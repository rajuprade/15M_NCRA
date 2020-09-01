
#ifndef __DEVSERVO_H__
#define __DEVSERVO_H__

#define TRK_INTERVAL 30 //sec

typedef struct {
   int trkflag, trkon ;   // To respond whether antenna tracking source or not
   float timezone, lat, longitude, longcorr;  // Lattitude, Longitude, Height
   float azcorr, elcorr;          // Antenna offset
   float elmin, elmax, azmin, azmax; // Minimum-max limit
} AntPara;

typedef struct {
   float dra, ddec;
   float daz, del;
   float length;
} ScanPara;

typedef struct {
   double trkTimer;
   double az, az15m ;
   double el, el15m ;
   double lctrise;
   double lctset;
} SrvPara;

typedef struct {
   int cmdid ; // Which command trackobject, rawtrack, trackoffazel, trackofradec, scan
   int outtrk ;
   float trkDuration; // in hrs
   struct tm lcltm;
   AntPara  antp ;
   ScanPara scanp ;
   SrvPara  latestTrk; // Want to use for AZ Scan rate and other stuff in future. Aug 17, 2012 JPK

  /* similar to sss structure in source.h */
   char     source_name[90];  // maximum 90 bytes can come from communication
   double   ra_mean;  //  RA mean, given ra
   double   dec_mean; // DEC mean, given dec
   double   epoch;  // Epoch
   double   ra_app;  // Apprent RA
   double   dec_app; // Aparent dec
   double   target_epoch;  // Target Epoch
   double   ra_offset; // RA Offset
   double   dra;   // DRA in sec
   double   dec_offset;// DEC OFFSET
   double   ddec;  // decoff in arcsec
   double   dradec_reftime;   // Reference Time for DRA DDEC
   double   az_offset; // AZ Offset
   double   daz;   // DAZ
   double   el_offset; // EL OFF
   double   del;   // ELOFF
   double   dazel_reftime;   // Reference time for DAZ and DELOFF
   double   curr_time;  // CurrentTime

} TrkPara;

#define   SrvParaSize sizeof(SrvPara)

extern TrkPara cmsTrk;
extern void initAntPara(AntPara *);
extern void initTrkPara(TrkPara *);

//extern int setAntPara(parseCMSCmd *,AntPara *);
//extern int setTrkPara(parseCMSCmd *, TrkPara *);
//extern void checkRange(parseCMSCmd *);
//extern int formServoCmd(parseCMSCmd *);

#endif // __WSERVO_H__
