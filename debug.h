#ifndef DEBUG_H
#define DEBUG_H

#ifndef CWDEBUG

#include <iostream>     // std::cerr
#include <cstdlib>      // std::exit, EXIT_FAILURE

#define AllocTag1(p)
#define AllocTag2(p, desc)
#define AllocTag_dynamic_description(p, data)
#define AllocTag(p, data)
#define Debug(STATEMENT...)
#define Dout(cntrl, data)
#define DoutFatal(cntrl, data) LibcwDoutFatal(, , cntrl, data)
#define ForAllDebugChannels(STATEMENT...)
#define ForAllDebugObjects(STATEMENT...)
#define LibcwDebug(dc_namespace, STATEMENT...)
#define LibcwDout(dc_namespace, d, cntrl, data)
#define LibcwDoutFatal(dc_namespace, d, cntrl, data) do { ::std::cerr << data << ::std::endl; ::std::exit(EXIT_FAILURE); } while(1)
#define LibcwdForAllDebugChannels(dc_namespace, STATEMENT...)
#define LibcwdForAllDebugObjects(dc_namespace, STATEMENT...)
#define NEW(x) new x
#define CWDEBUG_ALLOC 0
#define CWDEBUG_MAGIC 0
#define CWDEBUG_LOCATION 0
#define CWDEBUG_LIBBFD 0
#define CWDEBUG_DEBUG 0
#define CWDEBUG_DEBUGOUTPUT 0
#define CWDEBUG_DEBUGM 0
#define CWDEBUG_DEBUGT 0
#define CWDEBUG_MARKER 0

#else // CWDEBUG

// This must be defined before <libcwd/debug.h> is included and must be the
// name of the namespace containing your `dc' (Debug Channels) namespace
// (see below).  You can use any namespace(s) you like, except existing
// namespaces (like ::, ::std and ::libcwd).
#define DEBUGCHANNELS ::myproject::debug::channels
#include <libcwd/debug.h>

namespace myproject {
  namespace debug {

    void init(void);		// Initialize debugging code from main().
    void init_thread(void);	// Initialize debugging code from new threads.

    namespace channels {	// This is the DEBUGCHANNELS namespace, see above.
      namespace dc {		// 'dc' is defined inside DEBUGCHANNELS.

	using namespace libcwd::channels::dc;
	using libcwd::channel_ct;

	// Add the declaration of new debug channels here
	// and add their definition in a custom debug.cc file.
	extern channel_ct custom;

      } // namespace dc
    } // namespace DEBUGCHANNELS
  }
}

#endif // CWDEBUG

#endif // DEBUG_H
