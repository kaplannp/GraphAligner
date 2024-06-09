#ifndef vtuneConfiguration_H
#define vtuneConfiguration_H

#define VTUNE_ANALYSIS

#ifdef VTUNE_ANALYSIS
  #include <ittnotify.h>
#endif

#ifdef VTUNE_ANALYSIS
  #define ROI "ALL"
  //#define ROI "EXTENSION"
  //#define ROI "ALIGNMENT"
#endif


#endif
