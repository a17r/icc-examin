#/bin/bash


CONF_H=config.h
CONF=config
VERSION_A=0
VERSION_B=2
VERSION_C=6
VERSION=$VERSION_A.$VERSION_B$VERSION_C
VERSION_L=$VERSION_A.$VERSION_B.$VERSION_C
ZEIT="Mai 2004 - April 2005"

prefix=/opt/local

test -f error.txt && rm -v error.txt
test -f config && make clean

echo "# automatically generated file - do not edit" > $CONF
echo "/* automatically generated file - do not edit */" > $CONF_H
echo "prefix = $prefix" >> $CONF


echo ""

UNAME_=`uname`
if [ $? = 0 ] && [ $UNAME_ = "Darwin" ]; then
  echo "Darwin PPC              detected"
  echo "APPLE = 1" >> $CONF
  echo "OSX_H = -DHAVE_OSX" >> $CONF
else
  if [ $UNAME_ = "Linux" ]; then
    echo "LINUX = 1" >> $CONF
    echo "Linux system            detected"
  else
    if [ $UNAME_ = "SunOS" ]; then
      echo "SOLARIS = 1" >> $CONF
      echo "SunOS                   detected"
    else
      echo "ICC Examin may or may not compile on your $UNAME_ system"
    fi
  fi
fi

FLTK_=`fltk-config --cxxflags 2>>error.txt`
if [ $? = 0 ] && [ -n "$FLTK_" ]; then
  echo "FLTK `fltk-config --version`              detected"
  echo "#define HAVE_FLTK" >> $CONF_H
  echo "FLTK = 1" >> $CONF
  echo "FLTK_H = -DHAVE_FLTK `fltk-config --cxxflags`" >> $CONF
  echo "FLTK_LIBS = `fltk-config --use-images --use-gl --use-glut --ldflags`" >> $CONF
else
  echo "FLTK is not found; download: www.fltk.org"
fi


FLU_=`flu-config --cxxflags 2>>error.txt`
if [ $? = 0 ] && [ -n "$FLU_" ] && [ -n "$FLTK_" ]; then
  echo "FLU                     detected"
  echo "#define HAVE_FLU" >> $CONF_H
  echo "FLU = 1" >> $CONF
  echo "FLU_H = -DHAVE_FLU `flu-config --cxxflags`" >> $CONF
  echo "FLU_LIBS = `flu-config --ldflags`" >> $CONF
else
  echo "no FLU found, will not use it"
fi



if [ -f /usr/X11R6/include/X11/extensions/xf86vmode.h ]; then
  echo "X VidMode extension     detected"
  echo "#define HAVE_X" >> $CONF_H
  echo "X11 = 1" >> $CONF
  echo "X_H = -DHAVE_X" >> $CONF
else
  if [ $UNAME_ = "Linux" ]; then
    echo "X VidMode extension not found in /usr/X11R6/include/X11/extensions/xf86vmode.h"
  fi
fi


OY_=`oyranos-config 2>>error.txt`
if [ $? = 0 ] && [ -n $OY_ ]; then
  echo "Oyranos `oyranos-config --version`           detected"
  echo "#define HAVE_OY" >> $CONF_H
  echo "OY = 1" >> $CONF
  echo "OYRANOS_H = -DHAVE_OY `oyranos-config --cflags`" >> $CONF
  if [ -f /usr/X11R6/include/X11/extensions/xf86vmode.h ]; then
    echo "OYRANOS_LIBS = `oyranos-config --ld_x_flags`" >> $CONF
  else
    echo "OYRANOS_LIBS = `oyranos-config --ld_x_flags`" >> $CONF
  fi
else
  echo "no Oyranos found"
fi

`pkg-config  --atleast-version=1.14 lcms`
if [ $? = 0 ]; then
  echo "littleCMS `pkg-config --modversion lcms`          detected"
  echo "#define HAVE_LCMS" >> $CONF_H
  echo "LCMS = 1" >> $CONF
  echo "LCMS_H = `pkg-config --cflags lcms`" >> $CONF
  echo "LCMS_LIBS = `pkg-config --libs lcms`" >> $CONF
else
  echo "no or too old LCMS found,\n  need at least version 1.14, download: www.littlecms.com"
fi

echo "" >> $CONF
echo "VERSION_A = $VERSION_A" >> $CONF
echo "VERSION_B = $VERSION_B" >> $CONF
echo "VERSION_C = $VERSION_C" >> $CONF
echo "VERSION   = $VERSION" >> $CONF
echo "VERSION_L = $VERSION_L" >> $CONF
echo "src_dir = `pwd`/icc_examin_$VERSION" >> $CONF
echo "srcdir = `pwd`" >> $CONF

echo "#ifndef ICC_VERSION_H" > icc_version.h
echo "#define ICC_VERSION_H" >> icc_version.h
echo "" >> icc_version.h
echo "#define ICC_EXAMIN_VERSION_A $VERSION_A" >> icc_version.h
echo "#define ICC_EXAMIN_VERSION_B $VERSION_B" >> icc_version.h
echo "#define ICC_EXAMIN_VERSION_C $VERSION_C" >> icc_version.h
echo "#define ICC_EXAMIN_VERSION $VERSION" >> icc_version.h
echo "#define ICC_EXAMIN_V $VERSION" >> icc_version.h
echo "#define ICC_EXAMIN_D _(\"$ZEIT\")" >> icc_version.h
echo "" >> icc_version.h
echo "#endif //ICC_VERSION_H" >> icc_version.h

echo ""
echo ""


if [ `cat error.txt | wc -l` -lt 1 ]; then
  rm error.txt
fi