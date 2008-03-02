#!/bin/sh

ERROR=0

if [ -n "$PKG_CONFIG_PATH" ]; then
  PKG_CONFIG_PATH=$PKG_CONFIG_PATH:$libdir/pkgconfig
else
  PKG_CONFIG_PATH=$libdir/pkgconfig
fi
export PKG_CONFIG_PATH

if [ -n "$ELEKTRA" ] && [ "$ELEKTRA" -gt "0" ]; then
  if [ -z "$elektra_min" ]; then
    elektra_min="0.6"
  fi
  if [ -z "$elektra_max" ]; then
    elektra_max="0.6.100"
  fi
  if [ "$internalelektra" != "no" ]; then
   if [ `ls $ELEKTRA_VERSION | grep elektra | wc -l` -gt 0 ]; then
    echo "local copy of elektra   detected"
        echo "#define HAVE_ELEKTRA 1" >> $CONF_H
        echo "ELEKTRA = 1" >> $CONF
        echo "ELEKTRA_VERSION = $ELEKTRA_VERSION" >> $CONF
        echo "ELEKTRA_H = -I\$(ELEKTRA_VERSION)/src/include" >> $CONF
        echo "ELEKTRA_LIBS = \$(ELEKTRA_VERSION)/src/libelektra/libelektra.a" >> $CONF
        ELEKTRA_FOUND=1
   fi
  fi
  if [ -z $ELEKTRA_FOUND ]; then
    elektra_mod=`pkg-config --modversion elektra`
  fi
  if [ $? = 0 ] && [ -z $ELEKTRA_FOUND ]; then
    pkg-config  --atleast-version=$elektra_min elektra 2>>error.txt
    if [ $? = 0 ]; then
      pkg-config --max-version=$elektra_max elektra 2>>error.txt
      if [ $? = 0 ]; then
        test -n "$ECHO" && $ECHO "elektra `pkg-config --modversion elektra`           detected"
        echo "#define HAVE_ELEKTRA 1" >> $CONF_H
        echo "ELEKTRA = 1" >> $CONF
        echo "ELEKTRA_H = `pkg-config --cflags elektra`" >> $CONF
        if [ $elektra_mod = "0.6.4" ]; then
          echo "ELEKTRA_LIBS = `pkg-config --libs elektra` -lxml2 -ldb" >> $CONF
        else
          echo "ELEKTRA_LIBS = `pkg-config --libs elektra`" >> $CONF
        fi
        echo "ELEKTRA_SW = `pkg-config --cflags-only-I  elektra | sed 's/\-I// ; s%/include%/etc/kdb/%'`" >> $CONF
        ELEKTRA_FOUND=1
      else
        test -n "$ECHO" && $ECHO "!!! Elektra: !!!"
        test -n "$ECHO" && $ECHO "  too new Elektra found,"
        test -n "$ECHO" && $ECHO "  need a version not greater than $elektra_max, download: elektra.sf.net"
        ERROR=1
      fi
    else
      test -n "$ECHO" && $ECHO "!!! ERROR Elektra: !!!"
      test -n "$ECHO" && $ECHO "  no or too old elektra found,"
      test -n "$ECHO" && $ECHO "  need at least version $elektra_min, download: elektra.sf.net"
      ERROR=1
    fi
  fi
  if [ -z $ELEKTRA_FOUND ]; then
      test -n "$ECHO" && $ECHO $elektra_mod
      ERROR=1
  fi
fi

if [ -n "$OYRANOS" ] && [ "$OYRANOS" != "0" ]; then
  OY_=`oyranos-config 2>>error.txt`
  if [ $? = 0 ]; then
    test -n "$ECHO" && $ECHO "Oyranos `oyranos-config --version`           detected"
    echo "#define HAVE_OY 1" >> $CONF_H
    echo "OY = 1" >> $CONF
    echo "OYRANOS_H = `oyranos-config --cflags`" >> $CONF
    if [ -f /usr/X11R6/include/X11/extensions/xf86vmode.h ]; then
      echo "OYRANOS_LIBS = `oyranos-config --ld_x_flags`" >> $CONF
    else
      echo "OYRANOS_LIBS = `oyranos-config --ld_x_flags`" >> $CONF
    fi
  else
    test -n "$ECHO" && $ECHO "no Oyranos found"
  fi
fi

if [ -n "$LCMS" ] && [ $LCMS -gt 0 ]; then
  pkg-config  --atleast-version=1.14 lcms
  if [ $? = 0 ]; then
    test -n "$ECHO" && $ECHO "littleCMS `pkg-config --modversion lcms`          detected"
    echo "#define HAVE_LCMS 1" >> $CONF_H
    echo "LCMS = 1" >> $CONF
    echo "LCMS_H = `pkg-config --cflags lcms`" >> $CONF
    echo "LCMS_LIBS = `pkg-config --libs lcms`" >> $CONF
  else
    test -n "$ECHO" && $ECHO "!!! ERROR: no or too old LCMS found, !!!"
    test -n "$ECHO" && $ECHO "  need at least version 1.14, download: www.littlecms.com"
    ERROR=1
  fi
fi

if [ -n "$X11" ] && [ $X11 -gt 0 ]; then
  if [ -f /usr/X11R6/include/X11/Xlib.h ] ||
     [ -f /usr/include/X11/Xlib.h ] ||
     [ -f $includedir/X11/Xlib.h ]; then
    test -n "$ECHO" && $ECHO "X11                     detected"
    echo "#define HAVE_X 1" >> $CONF_H
    echo "X11 = 1" >> $CONF
    echo "X_H = -I/usr/X11R6/include -I/usr/include" >> $CONF
  elif [ $OSUNAME = "Linux" ]; then
    test -n "$ECHO" && $ECHO "X11 header not found in /usr/X11R6/include/X11/Xlib.h or"
    test -n "$ECHO" && $ECHO "/usr/include/X11/Xlib.h"
    X11=0
  fi
fi
if [ "$X11" = 1 ] && [ $X11 -gt 0 ]; then
  if [ -n "$XF86VMODE" ] && [ $XF86VMODE -gt 0 ]; then
    if [ -f /usr/X11R6/include/X11/extensions/xf86vmode.h ] ||
       [ -f /usr/include/X11/extensions/xf86vmode.h ] ||
       [ -f $includedir/X11/extensions/xf86vmode.h ]; then
      test -n "$ECHO" && $ECHO "X VidMode extension     detected"
      echo "#define HAVE_XF86VMODE 1" >> $CONF_H
      echo "XF86VMODE = 1" >> $CONF
      echo "XF86VMODE_LIB = -lXxf86vm" >> $CONF
    elif [ $OSUNAME = "Linux" ]; then
      test -n "$ECHO" && $ECHO "X VidMode extension not found in /usr/X11R6/include/X11/extensions/xf86vmode.h or"
      test -n "$ECHO" && $ECHO "/usr/include/X11/extensions/xf86vmode.h"
    fi
  fi

  if [ -n "$XINERAMA" ] && [ $XINERAMA -gt 0 ]; then
    if [ -f /usr/X11R6/include/X11/extensions/Xinerama.h ] ||
       [ -f /usr/include/X11/extensions/Xinerama.h ] ||
       [ -f $includedir/X11/extensions/Xinerama.h ]; then
      test -n "$ECHO" && $ECHO "X Xinerama              detected"
      echo "#define HAVE_XIN 1" >> $CONF_H
      echo "XIN = 1" >> $CONF
      echo "XINERAMA_LIB = -lXinerama" >> $CONF
    else
      if [ $OSUNAME = "Linux" ]; then
        test -n "$ECHO" && $ECHO "X Xinerma not found in /usr/X11R6/include/X11/extensions/Xinerama.h or"
        test -n "$ECHO" && $ECHO "/usr/include/X11/extensions/Xinerama.h"
      fi
    fi
  fi
  echo "X_CPP = \$(X_CPPFILES)" >> $CONF
  echo "X11_LIB_PATH = -L/usr/X11R6/lib\$(BARCH) -L/usr/lib\$(BARCH) -L\$(libdir)" >> $CONF
  echo "X11_LIBS=\$(X11_LIB_PATH) -lX11 \$(XF86VMODE_LIB) -lXpm -lXext \$(XINERAMA_LIB)" >> $CONF
fi

if [ -n "$FTGL" ] && [ $FTGL -gt 0 ]; then
  pkg-config  --atleast-version=1.0 ftgl
  if [ $? = 0 ]; then
    test -n "$ECHO" && $ECHO "FTGL      `pkg-config --modversion ftgl`         detected"
    echo "#define HAVE_FTGL 1" >> $CONF_H
    echo "FTGL = 1" >> $CONF
    echo "FTGL_H = `pkg-config --cflags ftgl`" >> $CONF
    echo "FTGL_LIBS = `pkg-config --libs ftgl`" >> $CONF
  else
    test -n "$ECHO" && $ECHO "  no or too old FTGL found, need FTGL to render text in OpenGL"
  fi
fi

if [ -z "$fltkconfig" ]; then
  fltkconfig="fltk-config"
fi
if [ -n "$FLTK" ] && [ $FLTK -gt 0 ]; then
  FLTK_=`$fltkconfig --cxxflags 2>>error.txt`
  if [ $? = 0 ] && [ -n "$FLTK_" ]; then
    test -n "$ECHO" && $ECHO "FLTK `$fltkconfig --version`              detected"
    if [ "0" -ne "`$fltkconfig --compile tests/fltk_test.cxx 2>&1 | grep lock | wc -l`" ]; then
      test -n "$ECHO" && $ECHO "!!! ERROR: FLTK has no threads support !!!"
      test -n "$ECHO" && $ECHO "           Configure FLTK with the --enable-threads option and recompile."
      ERROR=1
    else
      rm fltk_test
    fi
    echo "#define HAVE_FLTK 1" >> $CONF_H
    echo "FLTK = 1" >> $CONF
    echo "FLTK_H = `$fltkconfig --cxxflags | sed 's/-O[0-9]//'`" >> $CONF
    echo "FLTK_LIBS = `$fltkconfig --use-images --use-gl --ldflags`" >> $CONF
  else
    test -n "$ECHO" && $ECHO "!!! ERROR !!!"
    test -n "$ECHO" && $ECHO "           FLTK is not found; download: www.fltk.org"
    ERROR=1
  fi
fi

if [ -n "$FLU" ] && [ $FLU -gt 0 ]; then
  FLU_=`flu-config --cxxflags 2>>error.txt`
  if [ `$fltkconfig --version` = "1.1.7" ]; then
    echo -e "\c"
    test -n "$ECHO" && $ECHO "FLTK version 1.1.7 is not supported by FLU"
    if [ "$FLU" = 1 ]; then
      ERROR=1
    fi
  else
    if [ -n "$FLU_" ] && [ -n "$FLTK_" ]; then
      test -n "$ECHO" && $ECHO "FLU                     detected"
      echo "#define HAVE_FLU 1" >> $CONF_H
      echo "FLU = 1" >> $CONF
      echo "FLU_H = `flu-config --cxxflags`" >> $CONF
      echo "FLU_LIBS = `flu-config --ldflags --use-gl`" >> $CONF
    else
      if [ "$FLU" -gt 1 ]; then
        test -n "$ECHO" && $ECHO "   no FLU found, will not use it"
      else
        test -n "$ECHO" && $ECHO "ERROR:   FLU is not found; download:"
        test -n "$ECHO" && $ECHO "         http://www.osc.edu/~jbryan/FLU/http://www.osc.edu/~jbryan/FLU/"
        ERROR=1
      fi
    fi
  fi
fi

if [ -n "$DOXYGEN" ] && [ $DOXYGEN -gt 0 ]; then
  if [ "`which doxygen`" != "" ]; then
    test -n "$ECHO" && $ECHO "Doxygen `doxygen --version`           detected"
  else
    test -n "$ECHO" && $ECHO "Doxygen                 not detected"
  fi
fi

if [ -n "$LIBPNG" ] && [ $LIBPNG -gt 0 ]; then
  LIBPNG=libpng
  pkg-config  --atleast-version=1.0 $LIBPNG 2>>error.txt
  if [ $? != 0 ]; then
    LIBPNG=libpng12
    pkg-config  --atleast-version=1.0 $LIBPNG 2>>error.txt
  fi
  if [ $? = 0 ]; then
    test -n "$ECHO" && $ECHO "PNG `pkg-config --modversion $LIBPNG`               detected"
    echo "#define HAVE_PNG 1" >> $CONF_H
    echo "PNG = 1" >> $CONF
    echo "PNG_H = `pkg-config --cflags $LIBPNG`" >> $CONF
    echo "PNG_LIBS = `pkg-config --libs $LIBPNG`" >> $CONF
  else
    test -n "$ECHO" && $ECHO "no or too old libpng found,"
    test -n "$ECHO" && $ECHO "  need at least version 1.0, download: www.libpng.org"
  fi
fi

if [ -n "$LIBTIFF" ] && [ $LIBTIFF -gt 0 ]; then
  rm -f tests/libtest
  $CXX $CFLAGS -I$includedir tests/tiff_test.cxx $LDFLAGS -L$libdir -ltiff -o tests/libtest
    if [ -f tests/libtest ]; then
      test -n "$ECHO" && $ECHO "`tests/libtest`
                        detected"
      echo "#define HAVE_TIFF 1" >> $CONF_H
      echo "TIFF = 1" >> $CONF
      rm tests/libtest
    else
      test -n "$ECHO" && $ECHO "no or too old libtiff found,"
    fi
fi

if [ -n "$PO" ] && [ $PO -gt 0 ]; then
  pos_dir="`ls po/*.po 2> /dev/null`"
  LING="`echo $pos_dir`"
  LINGUAS="`echo $pos_dir | sed 's/\.po//g ; s/po\///g'`"
  echo "LINGUAS = $LINGUAS" >> $CONF
  echo "translations available: $LINGUAS"
  echo "LING = $LING" >> $CONF
  echo "#define USE_GETTEXT 1" >> $CONF_H
fi

if [ -n "$PREPARE_MAKEFILES" ] && [ $PREPARE_MAKEFILES -gt 0 ]; then
  if [ -n "$MAKEFILE_DIR" ]; then
    for i in $MAKEFILE_DIR; do
      echo preparing Makefile in "$i/"
      if [ $OSUNAME = "BSD" ]; then
        test -f "$i/makefile".in && cat  "$i/makefile".in | sed 's/^\#if/.if/g ; s/^\#end/.end/g '  >> "$i/makefile"
      else
        test -f "$i/makefile".in && cat  "$i/makefile".in | sed 's/^\#if/if/g ; s/^\#elif/elif/g ; s/^\#else/else/g ; s/^\ \ \#if/\ \ if/g ; s/^\#end/end/g '  >> "$i/makefile"
      fi
      mv "$i/makefile" "$i/Makefile"
    done
  fi
fi


if [ -n "$DEBUG" ] && [ $DEBUG -gt 0 ]; then
  if [ "$debug" -eq "1" ]; then
    DEBUG_="-Wall -g -DDEBUG --pedantic"
    echo "DEBUG = $DEBUG_" >> $CONF
    echo "DEBUG_SWITCH = -v" >> $CONF
    echo "DEBUG_SWITCH = -v" >> $CONF_I18N
  fi
fi

# we cannot reimport, just return
if [ "$ERROR" -ne "0" ]; then 
  echo "error" > error.tmp
fi
exit $ERROR

