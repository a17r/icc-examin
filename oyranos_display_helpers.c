/**
 *  Oyranos is an open source Colour Management System 
 * 
 *  @par Copyright:
 *            2009-2012 (C) Kai-Uwe Behrmann
 *
 *  @author   Kai-Uwe Behrmann <ku.b@gmx.de>
 *  @par License:
 *            new BSD <http://www.opensource.org/licenses/bsd-license.php>
 *  @since    2010/09/05
 *
 *  Oyranos helpers for handling on screen display of images.
 */

#include <oyranos.h>
#include <alpha/oyranos_alpha.h>
#include "oyranos_display_helpers.h"

int oy_display_verbose = 0;

/** Function oyConversion_FromImageForDisplay
 *  @brief   generate a Oyranos graph from a image file name
 *
 *  @param[in]     image_in            input
 *  @param[in]     image_out           output
 *  @param[out]    icc_node            used icc node, owned by caller
 *  @param[in]     flags               for inbuild defaults |
 *                                     oyOPTIONSOURCE_FILTER;
 *                                     for options marked as advanced |
 *                                     oyOPTIONATTRIBUTE_ADVANCED |
 *                                     OY_SELECT_FILTER |
 *                                     OY_SELECT_COMMON
 *  @param[in]     data_type           the desired data type for output
 *  @param[in]     obj                 Oyranos object (optional)
 *  @return                            generated new graph, owned by caller
 *
 *  @version Oyranos: 0.4.0
 *  @since   2012/01/21 (Oyranos: 0.4.0)
 *  @date    2012/01/22
 */
oyConversion_s * oyConversion_FromImageForDisplay  (
                                       oyImage_s         * image_in,
                                       oyImage_s         * image_out,
                                       oyFilterNode_s   ** icc_node,
                                       uint32_t            flags,
                                       oyDATATYPE_e        data_type,
                                       oyObject_s          obj )
{
  oyFilterNode_s * in, * out, * icc;
  int error = 0;
  oyConversion_s * conversion = 0;
  oyOptions_s * options = 0;

  if(!image_in || !image_out)
    return NULL;

  /* start with an empty conversion object */
  conversion = oyConversion_New( obj );
  /* create a filter node */
  in = oyFilterNode_NewWith( "//" OY_TYPE_STD "/root", 0, obj );
  /* set the above filter node as the input */
  oyConversion_Set( conversion, in, 0 );
  /* set the image buffer */
  oyFilterNode_DataSet( in, (oyStruct_s*)image_in, 0, 0 );


  /* create a new filter node */
  icc = out = oyFilterNode_NewWith( "//" OY_TYPE_STD "/icc", options, obj );
  /* append the new to the previous one */
  error = oyFilterNode_Connect( in, "//" OY_TYPE_STD "/data",
                                out, "//" OY_TYPE_STD "/data", 0 );
  if(error > 0)
    fprintf( stderr, "could not add  filter: %s\n", "//" OY_TYPE_STD "/icc" );

  /* Set the image to the first/only socket of the filter node.
   * oyFilterNode_Connect() has now no chance to copy it it the other nodes.
   * We rely on resolving the image later.
   */
  oyFilterNode_DataSet( in, (oyStruct_s*)image_out, 0, 0 );

  /* swap in and out */
  in = out;


  /* create a node for preparing the image for displaying */
  out = oyFilterNode_NewWith( "//" OY_TYPE_STD "/display", 0, obj );
  options = oyFilterNode_OptionsGet( out, OY_SELECT_FILTER );
  /* 8 bit data for FLTK */
  error = oyOptions_SetFromInt( &options,
                                "//" OY_TYPE_STD "/display/datatype",
                                data_type, 0, OY_CREATE_NEW );
  /* alpha might be support once by FLTK? */
  error = oyOptions_SetFromInt( &options,
                                "//" OY_TYPE_STD "/display/preserve_alpha",
                                1, 0, OY_CREATE_NEW );
  oyOptions_Release( &options );
  /* append the node */
  error = oyFilterNode_Connect( in, "//" OY_TYPE_STD "/data",
                                out, "//" OY_TYPE_STD "/data", 0 );
  if(error > 0)
    fprintf( stderr, "could not add  filter: %s\n", "//" OY_TYPE_STD "/display" );
  in = out;


  /* add a closing node */
  out = oyFilterNode_NewWith( "//" OY_TYPE_STD "/output", 0, obj );
  error = oyFilterNode_Connect( in, "//" OY_TYPE_STD "/data",
                                out, "//" OY_TYPE_STD "/data", 0 );
  /* set the output node of the conversion */
  oyConversion_Set( conversion, 0, out );

  /* apply policies */
  /*error = oyOptions_SetFromText( &options, "//" OY_TYPE_STD "//verbose",
                                 "true", OY_CREATE_NEW );*/
  oyConversion_Correct( conversion, "//" OY_TYPE_STD "/icc", flags,
                        options );
  oyOptions_Release( &options );


  *icc_node = icc;

  return conversion;
}
/** Function oyConversion_FromImageFileNameForDisplay
 *  @brief   generate a Oyranos graph from a image file name
 *
 *  @param[in]     file_name           name of image file
 *  @param[out]    icc_node            used icc node, owned by caller
 *  @param[in]     flags               for inbuild defaults |
 *                                     oyOPTIONSOURCE_FILTER;
 *                                     for options marked as advanced |
 *                                     oyOPTIONATTRIBUTE_ADVANCED |
 *                                     OY_SELECT_FILTER |
 *                                     OY_SELECT_COMMON
 *  @param[in]     data_type           the desired data type for output
 *  @param[in]     obj                 Oyranos object (optional)
 *  @return                            generated new graph, owned by caller
 *
 *  @version Oyranos: 0.3.0
 *  @since   2010/09/05 (Oyranos: 0.1.11)
 *  @date    2011/02/16
 */
oyConversion_s * oyConversion_FromImageFileNameForDisplay  (
                                       const char        * file_name,
                                       oyFilterNode_s   ** icc_node,
                                       uint32_t            flags,
                                       oyDATATYPE_e        data_type,
                                       oyObject_s          obj )
{
  oyFilterNode_s * in, * out, * icc;
  int error = 0;
  oyConversion_s * conversion = 0;
  oyOptions_s * options = 0;
  oyImage_s * image_in = 0;

  if(!file_name)
    return NULL;

  /* start with an empty conversion object */
  conversion = oyConversion_New( obj );
  /* create a filter node */
  in = oyFilterNode_NewWith( "//" OY_TYPE_STD "/file_read.meta", 0, obj );
  /* set the above filter node as the input */
  oyConversion_Set( conversion, in, 0 );

  /* add a file name argument */
  /* get the options of the input node */
  if(in)
  options = oyFilterNode_OptionsGet( in, OY_SELECT_FILTER );
  /* add a new option with the appropriate value */
  error = oyOptions_SetFromText( &options, "//" OY_TYPE_STD "/file_read/filename",
                                 file_name, OY_CREATE_NEW );
  /* release the options object, this means its not any more refered from here*/
  oyOptions_Release( &options );

  /* create a new filter node */
  icc = out = oyFilterNode_NewWith( "//" OY_TYPE_STD "/icc", options, obj );
  /* append the new to the previous one */
  error = oyFilterNode_Connect( in, "//" OY_TYPE_STD "/data",
                                out, "//" OY_TYPE_STD "/data", 0 );
  if(error > 0)
    fprintf( stderr, "could not add  filter: %s\n", "//" OY_TYPE_STD "/icc" );

  /* Set the image to the first/only socket of the filter node.
   * oyFilterNode_Connect() has now no chance to copy it it the other nodes.
   * We rely on resolving the image later.
   */
  oyFilterNode_DataSet( in, (oyStruct_s*)image_in, 0, 0 );

  /* swap in and out */
  in = out;


  /* create a node for preparing the image for displaying */
  out = oyFilterNode_NewWith( "//" OY_TYPE_STD "/display", 0, obj );
  options = oyFilterNode_OptionsGet( out, OY_SELECT_FILTER );
  /* 8 bit data for FLTK */
  error = oyOptions_SetFromInt( &options,
                                "//" OY_TYPE_STD "/display/datatype",
                                data_type, 0, OY_CREATE_NEW );
  /* alpha might be support once by FLTK? */
  error = oyOptions_SetFromInt( &options,
                                "//" OY_TYPE_STD "/display/preserve_alpha",
                                1, 0, OY_CREATE_NEW );
  oyOptions_Release( &options );
  /* append the node */
  error = oyFilterNode_Connect( in, "//" OY_TYPE_STD "/data",
                                out, "//" OY_TYPE_STD "/data", 0 );
  if(error > 0)
    fprintf( stderr, "could not add  filter: %s\n", "//" OY_TYPE_STD "/display" );
  in = out;


  /* add a closing node */
  out = oyFilterNode_NewWith( "//" OY_TYPE_STD "/output", 0, obj );
  error = oyFilterNode_Connect( in, "//" OY_TYPE_STD "/data",
                                out, "//" OY_TYPE_STD "/data", 0 );
  /* set the output node of the conversion */
  oyConversion_Set( conversion, 0, out );

  /* apply policies */
  /*error = oyOptions_SetFromText( &options, "//" OY_TYPE_STD "//verbose",
                                 "true", OY_CREATE_NEW );*/
  oyConversion_Correct( conversion, "//" OY_TYPE_STD "/icc", flags,
                        options );
  oyOptions_Release( &options );


  *icc_node = icc;

  return conversion;
}


/** Function oyDrawScreenImage
 *  @brief   generate a Oyranos image from a given context for display
 *
 *  The function asks the 'oydi' node to provide parameters to render a
 *  oyImage_s from a prepared oyConversion_s context.
 *
 *  @param[in]     context             the Oyranos graph
 *  @param[in]     display_rectangle   absolute coordinates of visible image
 *                                     in relation to display
 *  @param[in,out] old_display_rectangle
 *                                     rembering of display_rectangle
 +  @param[in,out] old_roi_rectangle   remembering of ticket's ROI (optional)
 *  @param[in]     system_type         the system dependent type specification
 *  @param[in]     display             the system display with system_type:
 *                                     - "X11": a Display object
 *  @param[in]     window              the system window with system_type:
 *                                     - "X11": a Window ID
 *  @param[in]     dirty               explicite redraw
 *  @param[out]    image               the image from graph to display
 *  @return                            0 - success, -1 - issue, >=  1 - error
 *
 *  @version Oyranos: 0.4.0
 *  @since   2010/09/05 (Oyranos: 0.1.11)
 *  @date    2012/01/24
 */
int  oyDrawScreenImage               ( oyConversion_s    * context,
                                       oyPixelAccess_s   * ticket,
                                       oyRectangle_s     * display_rectangle,
                                       oyRectangle_s     * old_display_rectangle,
                                       oyRectangle_s     * old_roi_rectangle,
                                       const char        * system_type,
                                       oyDATATYPE_e        data_type_request,
                                       void              * display,
                                       void              * window,
                                       int                 dirty,
                                       oyImage_s         * image )
{
    if(context)
    {
      int X = display_rectangle->x;
      int Y = display_rectangle->y;
      int W = display_rectangle->width;
      int H = display_rectangle->height;
      int channels = 0;
      oyRectangle_s * disp_rectangle = 0;
      oyOptions_s * image_tags = 0;
      oyDATATYPE_e data_type = oyUINT8;
      oyPixel_t pt = 0;

      if(!image)
        return 1;
      if( W <= 0 || H <= 0)
        return -1;

      image_tags = oyImage_TagsGet( image );

    if(window && strcmp("X11", system_type) == 0)
    {
#if defined(HAVE_X)
      /* add X11 window and display identifiers to output image */
      oyOption_s * o = 0;
      Display *disp = (Display*) display;
      Window  w = (Window) window;
      int count = oyOptions_CountType( image_tags,
                                       "//" OY_TYPE_STD "/display/window_id",
                                       oyOBJECT_BLOB_S );
      if(!count && w)
      {
        oyBlob_s * win_id = oyBlob_New(0),
                 * display_id = oyBlob_New(0);
        if(win_id)
        {
          oyBlob_SetFromStatic( win_id, (oyPointer)w, 0, 0 );
          o = oyOption_FromRegistration( "//" OY_TYPE_STD "/display/window_id",
                                         0 );
          oyOption_StructMoveIn( o, (oyStruct_s**)&win_id );
          oyOptions_MoveIn( image_tags, &o, -1 );

          oyBlob_SetFromStatic( display_id, (oyPointer)disp, 0, 0 );
          o = oyOption_FromRegistration( "//" OY_TYPE_STD "/display/display_id",
                                         0 );
          oyOption_StructMoveIn( o, (oyStruct_s**)&display_id );
          oyOptions_MoveIn( image_tags, &o, -1 );

          oyOptions_SetFromText( &image_tags,
                                 "//" OY_TYPE_STD "/display/display_name",
                                 DisplayString(disp), OY_CREATE_NEW );

        } else
          printf("%s:%d WARNING: no X11 Window obtained or\n"
                 "   no oyBlob_s allocateable\n", __FILE__,__LINE__);

      }
#endif
   }
      /* check if the actual data can be displayed */
      pt = oyImage_PixelLayoutGet( image );
      data_type = oyToDataType_m( pt );
      channels = oyToChannels_m( pt );
      if(pt != 0 &&
         ((channels != 4 && channels != 3) || data_type != data_type_request))
      {
        printf( "WARNING: wrong image data format: %s\n%s\n"
                "need 4 or 3 channels with %s\n",
                oyOptions_FindString( image_tags, "filename", 0 ),
                image ? oyObject_GetName( image->oy_, oyNAME_NICK ) : "",
                oyDatatypeToText( data_type_request ) );
        return 1;
      }


      /* Inform about the images display coverage.  */
      disp_rectangle = (oyRectangle_s*) oyOptions_GetType( image_tags, -1,
                                    "display_rectangle", oyOBJECT_RECTANGLE_S );
      oyRectangle_SetGeo( disp_rectangle, X,Y,W,H );

      oyOptions_Release( &image_tags );

      /* decide wether to refresh the cached rectangle of our static image */
      if( context->out_ &&
          /* Did the window area move? */
         ((!oyRectangle_IsEqual( disp_rectangle, old_display_rectangle ) ||
           /* Something explicite to update? */
           (old_roi_rectangle &&
            !oyRectangle_IsEqual( ticket->output_image_roi, old_roi_rectangle ))||
           /* Did the image move? */
           ticket->start_xy[0] != ticket->start_xy_old[0] ||
           ticket->start_xy[1] != ticket->start_xy_old[1]) ||
           dirty ))
      {
#ifdef DEBUG_
        printf( "%s:%d new display rectangle: %s +%d+%d\n", __FILE__,__LINE__,
                oyRectangle_Show(disp_rectangle), X, Y ),
#endif

        /* convert the image data */
        oyConversion_RunPixels( context, ticket );

        /* remember the old rectangle */
        oyRectangle_SetByRectangle( old_display_rectangle, disp_rectangle );
        oyRectangle_SetByRectangle( old_roi_rectangle,ticket->output_image_roi);
        ticket->start_xy_old[0] = ticket->start_xy[0];
        ticket->start_xy_old[1] = ticket->start_xy[1];
      }
    }
  return 0;
}

extern "C" { int oyWriteMemToFile_(const char* name, const void* mem, size_t size); }

oyProfile_s * getEditingProfile      ( )
{
  static oyProfile_s * editing = NULL;

  if(!editing)
  {
    oyOption_s *matrix = oyOption_FromRegistration("///colour_matrix."
              "from_primaries."
              "redx_redy_greenx_greeny_bluex_bluey_whitex_whitey_gamma", NULL );
    /* http://www.color.org/chardata/rgb/rommrgb.xalter
     * original gamma is 1.8, we adapt to typical LCD gamma of 2.2 */
    oyOption_SetFromDouble( matrix, 0.7347, 0, 0);
    oyOption_SetFromDouble( matrix, 0.2653, 1, 0);
    oyOption_SetFromDouble( matrix, 0.1596, 2, 0);
    oyOption_SetFromDouble( matrix, 0.8404, 3, 0);
    oyOption_SetFromDouble( matrix, 0.0366, 4, 0);
    oyOption_SetFromDouble( matrix, 0.0001, 5, 0);
    oyOption_SetFromDouble( matrix, 0.3457, 6, 0);
    oyOption_SetFromDouble( matrix, 0.3585, 7, 0);
    oyOption_SetFromDouble( matrix, 2.2, 8, 0);

    oyOptions_s * opts = oyOptions_New(0),
                * result = 0;

    oyOptions_MoveIn( opts, &matrix, -1 );
    oyOptions_Handle( "//"OY_TYPE_STD"/create_profile.icc",
                                opts,"create_profile.icc_profile.colour_matrix",
                                &result );

    editing = (oyProfile_s*)oyOptions_GetType( result, -1, "icc_profile",
                                               oyOBJECT_PROFILE_S );
    oyOptions_Release( &result );

    oyProfile_AddTagText( editing, icSigProfileDescriptionTag,
                                            "ICC Examin ROMM gamma 2.2" );

    if(oy_debug)
    {
      size_t size = 0;
      char * data = (char*) oyProfile_GetMem( editing, &size, 0, malloc );
      oyWriteMemToFile_( "ICC Examin ROMM gamma 2.2.icc", data, size );
    }
  }

  return editing;
}

