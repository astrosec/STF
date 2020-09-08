/**
 * @file   igrf.cpp
 * @brief  NJHILSから持ってきたIGRF計算モジュールを，igrf名前空間でラップして使用．
 * Use the IGRF calculation module brought from wrapping in the igrf namespace
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
/**********************/
/***     igrf.c     ***/
/****************************************************************************/
/* Usage from FORTRAN :     ( All variables are in single precision )       */
/*      First specify the Generation Number with the Year of Calc.          */
/*          by  CALL gigrf(NGEN, YEAR),                                     */
/*        or specify the Model Type (IGRF/DGRF/PGRF) with the Year of Calc. */
/*          by  CALL sigrf(YEAR), CALL sdgrf(YEAR) or CALL spgrf(YEAR) .    */
/*      Then, CALL igrfc(FI, FK, H, F) gives TotalForce (F) of that model   */
/*          at the point of Lat.=FI, Long.=FK, Alt.=H                       */
/*      If other components are desired, CALL igrfm(FM) .                   */
/*          Here FM is an array with 6 elements, which correspond to        */
/*              North(X), East(Y), Downward(Z), Horizontal(H) components,   */
/*              Inclination(I) and Declination(D).                          */
/*  Unit Convention:  Lat.(FI), Long.(FK), Inc.(I), Dec.(D) are in degrees, */
/*                    Mag.Fields(F,X,Y,Z, H) in nT, and Alt.(H) in meters.   */
/****************************************************************************/
/* Prototype definition for C :                                             */
/*--------------------------------------------------------------------------*/
/*   < Conventional Functions and their FORTRAN Interfaces >                */
/*--------------------------------------------------------------------------*/
/*  void sigrf(double year);         |  void sigrf_(float *year);           */
/*   / void sdgrf(double year);      |   / void sdgrf_(float *year);        */
/*   / void spgrf(double year);      |   / void spgrf_(float *year);        */
/*  void gigrf(int gen, double year);|  void gigrf_(int *gen, float *year); */
/*  void igrfc(double fi, double fk, |  void igrfc_(float *fi, float *fk,   */
/*             double h, double *f); |              float *h, float *f);    */
/*  void igrfm(double fm[6]);        |  void igrfm_(float fm[6]);           */
/*--------------------------------------------------------------------------*/
/*   < Substantial Calculation Functions >                                  */
/*--------------------------------------------------------------------------*/
/*  void field(double are, double aflat, double ara, int maxoda);           */
/*  void tcoef(double agh[MxOD+1][MxOD+1], double aght[MxOD+1][MxOD+1],     */
/*             double atzero, int kexta, double aext[3]);                   */
/*  void tyear(double ayear);                                               */
/*  void mfldg(double alat, double alon, double ahi,                        */
/*             double *ax, double *ay, double *az, double *af);             */
/*  void mfldc(double athe, double alon, double ar,                         */
/*             double *ax, double *ay, double *az, double *af);             */
/*  void gcomp(double *axg, double *ayg, double *azg);                      */
/****************************************************************************/

#include <stdio.h>
//#include <string.h>
#include <math.h>
#include <stdlib.h>
//#include <iostream>
#include "../sgp4/sgp4ext.h"
using namespace std;
using namespace sgp4;
#include "igrf.h"

namespace igrf {

double testglobal[3];

/*--------------------*/
/*   Basic Routines   */
/*--------------------*/

#define MxOD    19
#define URAD    (180./3.14159265359)

#define PI			3.14159265358979323846
#define DEG2RAD		0.017453292519943295769236907684886	// PI/180
#define RAD2DEG		(180/PI)


static double ra, rpre, re, re2, re4, rp, rp2, rp4, tzero;
static int maxod, kg, kgc, kr, kth, kph, kext;
static double blat, blon, bhi, br, bthe, bthc;
static double rlat, slat, slat2, clat, clat2;
static double r, the, phi, cth, sth, cph, sph;
static double x, y, z, f, ext0, ext1, ext2;
static double gh[MxOD+1][MxOD+1], ght[MxOD+1][MxOD+1], g[MxOD+1][MxOD+1];
static double rar[MxOD+1], csp[MxOD+1], snp[MxOD+1], p[MxOD+2][MxOD+1];

static double vgh[MxOD+1][MxOD+1], vght[MxOD+1][MxOD+1];

static void fcalc(void)     /* This is an internal function */
{   double t, pn1m, tx, ty, tz; int n, m;
    if (kr != 0) {
        kr=0; t=ra/r; rar[0]=t*t;
        for (n=0; n<maxod; n++) rar[n+1]=rar[n]*t;
    }
    if (kth != 0) {
        kth=0; p[0][0]=1.; p[1][0]=0.;
        p[0][1]=cth; p[1][1]=sth; p[2][0]=-sth; p[2][1]=cth;
        for (n=1; n<maxod; n++) {
            p[0][n+1]=(p[0][n]*cth*(n+n+1)-p[0][n-1]*n)/(n+1);
            p[n+2][0]=(p[0][n+1]*cth-p[0][n])*(n+1)/sth;
            for (m=0; m<=n; m++) {
                pn1m=p[m][n+1];
                p[m+1][n+1]=(p[m][n]*(n+m+1)-pn1m*cth*(n-m+1))/sth;
                p[n+2][m+1]=pn1m*(n+m+2)*(n-m+1)-p[m+1][n+1]*cth*(m+1)/sth;
            }
        }
    }
    if (kph != 0) {
        kph=0; csp[0]=1.; snp[0]=0.;
        for (m=0; m<maxod; m++) {
            csp[m+1]=csp[m]*cph-snp[m]*sph;
            snp[m+1]=snp[m]*cph+csp[m]*sph;
        }
    }
    x=0.; y=0.; z=0.;
    for (n=0; n<maxod; n++) {
        tx=g[0][n+1]*p[n+2][0]; ty=0.; tz=g[0][n+1]*p[0][n+1];
        for (m=0; m<=n; m++) {
            tx+=(g[m+1][n+1]*csp[m+1]+g[n+1][m]*snp[m+1])*p[n+2][m+1];
            ty+=(g[m+1][n+1]*snp[m+1]-g[n+1][m]*csp[m+1])*p[m+1][n+1]*(m+1);
            tz+=(g[m+1][n+1]*csp[m+1]+g[n+1][m]*snp[m+1])*p[m+1][n+1];
        }
        x+=rar[n+1]*tx; y+=rar[n+1]*ty; z-=rar[n+1]*tz*(n+2);
    }
    y/=sth;
    if (kext != 0) {
        t=ext1*cph+ext2*sph; x-=(ext0*cth+t*sth);
        y+=(ext1*sph-ext2*cph); z+=(ext0*sth-t*cth);
    }
    f=sqrt(x*x+y*y+z*z);
}

void field(double are, double aflat, double ara, int maxoda)
{   ra=ara; maxod=maxoda; rpre=1.-1./aflat;
    re=are; re2=re*re; re4=re2*re2; rp=re*rpre; rp2=rp*rp; rp4=rp2*rp2;
    kg=2; kgc=0; kph=1;
}

void tcoef(double agh[MxOD+1][MxOD+1], double aght[MxOD+1][MxOD+1],
            double atzero, int kexta, double aext[3])
{   int nn, mm; double fac;
    tzero=atzero; kext=kexta; gh[0][0]=0.; ght[0][0]=0.;
    for (nn=1; nn<=maxod; nn++) {
        gh[0][nn]=agh[0][nn]; ght[0][nn]=aght[0][nn]; fac=sqrt(2.);
        for (mm=1; mm<=nn; mm++) {
            fac/=sqrt((double)((nn+mm)*(nn-mm+1)));
            gh[mm][nn]=agh[mm][nn]*fac; gh[nn][mm-1]=agh[nn][mm-1]*fac;
            ght[mm][nn]=aght[mm][nn]*fac; ght[nn][mm-1]=aght[nn][mm-1]*fac;
        }
    }
    if (kext == 0) { ext0=0.; ext1=0.; ext2=0.; }
    else { ext0=aext[0]; ext1=aext[1]; ext2=aext[2]; }
}

void tyear(double ayear)
{   double dyear; int nn, mm;
    dyear=ayear-tzero;
    for (nn=0; nn<=maxod; nn++) {
        for (mm=0; mm<=maxod; mm++) {
            g[mm][nn]=gh[mm][nn]+ght[mm][nn]*dyear;
        }
    }
}

void mfldg(double alat, double alon, double ahi,
            double *ax, double *ay, double *az, double *af)
{   double hi, rm2, rm, rrm;
    if ((kg!=1) || (blat!=alat) || (bhi!=ahi)) {
        kg=1; kr=1; kth=1; blat=alat; bhi=ahi;
        rlat=alat/URAD; hi=ahi; slat=sin(rlat); slat2=slat*slat;
        clat2=1.-slat2; rm2=re2*clat2+rp2*slat2; rm=sqrt(rm2);
        rrm=(re4*clat2+rp4*slat2)/rm2; r=sqrt(rrm+2.*hi*rm+hi*hi);
        cth=slat*(hi+rp2/rm)/r; sth=sqrt(1.-cth*cth);
    }
    if (blon != alon) kph=1;
    if (kph != 0) { blon=alon; phi=alon/URAD; cph=cos(phi); sph=sin(phi); }
    fcalc(); *ax=x; *ay=y; *az=z; *af=f;
}

void mfldc(double athe, double alon, double ar,
            double *ax, double *ay, double *az, double *af)
{   if (kg == 0) {
        if (bthe != athe) kth=1;
        if (br != ar) kr=1;
    }
    else { kg=0; kr=1; kth=1; }
    if (kr != 0) { br=ar; r=ar; }
    if (kth != 0) { bthe=athe; the=athe/URAD; cth=cos(the); sth=sin(the); }
    if (blon != alon) kph=1;
    if (kph != 0) { blon=alon; phi=alon/URAD; cph=cos(phi); sph=sin(phi); }
    fcalc(); *ax=x; *ay=y; *az=z; *af=f;
}

//地心座標から測地座標に変換
//Convert geocentric coordinates to geodetic coordinates
void gcomp(double *axg, double *ayg, double *azg)
{   double bthc, rc, rs, rep2, tlat, tlat2, rlatp, rmc, rmc2, rmc3, ffp, ff;
    double cga, sga, xg, zg;
    if (kg == 1) { kgc=0; clat=sqrt(clat2); }
    else if ((kgc==0) || (bthc!=bthe)) {
        kgc=1; bthc=bthe; slat=cth; clat=sth;
        if (clat > 1.5e-9) {
            rc=r*cth; rs=r*sth; rep2=re2-rp2; tlat=slat/clat;
            tlat2=tlat*tlat; rlat=atan(tlat);
            do {rlatp=rlat; rmc2=re2+rp2*tlat2; rmc=sqrt(rmc2);
                rmc3=rmc2*rmc; ffp=rp2*rep2*tlat/rmc3+rc/tlat2;
                ff=rep2/rmc+rc/tlat-rs; tlat+=ff/ffp;
                tlat2=tlat*tlat; rlat=atan(tlat);
            } while (fabs(rlat-rlatp) > 1.5e-9);
            clat2=1./(1.+tlat2); clat=sqrt(clat2); slat=tlat*clat;
        }
    }
    cga=cth*slat+sth*clat; sga=cth*clat-sth*slat;
    xg=x*cga-z*sga; zg=x*sga+z*cga;
    *axg=xg; *ayg=y; *azg=zg;
}

/*---------------------------*/
/*   Conventional Routines   */
/*---------------------------*/

#define MxGEN   10
#define RAD     (180./3.14159265359)
#define MxMOD   19
#define MxELM   ((MxMOD+1)*(MxMOD+1)-1)
#define MxCOL   50
#define LLINE   (MxCOL*9 + 10)

//GIGRFの計算（G, D,P-GRFの区別なく計算）
//WGS84モデルで計算
////GIGRF calculation (calculation without distinguishing G, D, P-GRF)
//Calculated with WGS84 model
void gigrf(int gen, double year)
{   int maxod, i, n, m, l, k, ncol, nlin;
    double y1, y2, yr1, yr2;
    double tzero, dmy[3], cb[MxELM], cv[MxELM];
    char path[]="igrf10.coef";
    char file[]="igrf10.coef";
    char *pstr, *line, buf[LLINE];
    FILE *fp;
    if ((gen<1) || (MxGEN<gen))
        { fprintf(stderr, "gigrf: unknown  NGEN = %d\n", gen); exit(1); }
    strcpy(file, path);
    if ((pstr=strstr(file, "10")) == NULL)
        { fprintf(stderr, "gigrf: filename invalid\n"); exit(1); }
    sprintf(buf, "%02d", gen); strncpy(pstr, buf, 2);
    if ((fp=fopen(file, "r")) == NULL)
        { fprintf(stderr, "gigrf: file not found\n"); exit(1); }
    if (fgets(buf, LLINE, fp) == NULL)
        { fprintf(stderr, "gigrf: file empty\n"); exit(1); }
    if (sscanf(buf, "%d%d%lf%lf",&maxod,&ncol,&y1,&y2) != 4)
        { fprintf(stderr, "gigrf: Line-1 format error\n"); exit(1); }
    if ((maxod<8) || (maxod>MxMOD) || (ncol<2) || (ncol>MxCOL))
        { fprintf(stderr, "gigrf: Line-1 invalid\n"); exit(1); }
    nlin = (maxod+1)*(maxod+1) - 1;
    if ((year<y1) || (year>y2))
        fprintf(stderr, "gigrf: IGRF-%02d not defined for %9.3lf\n", gen, year);
    if (fgets(buf, LLINE, fp) == NULL)
        { fprintf(stderr, "gigrf: EOF before Line-2\n"); exit(1); }
    line = &buf[1];
    if (sscanf(line, "%*c%*d%*d%lf%n",&yr2,&n) == EOF)
        { fprintf(stderr, "gigrf: Line-2 invalid\n"); exit(1); }
    for (l=2; l<ncol; l++) {
        line += n; yr1 = yr2;
        if (sscanf(line, "%lf%n",&yr2,&n) == EOF)
            { fprintf(stderr, "gigrf: Line-2 short\n"); exit(1); }
        if (year < yr2) break;
    }
    for (i=0; i<nlin; i++) {
        if (fgets(buf, LLINE, fp) == NULL)
            { fprintf(stderr, "gigrf: EOF before Line-%d\n", i+3); exit(1); }
        line = &buf[0];
        if (sscanf(line, "%*c%*d%*d%n",&n) == EOF)
            { fprintf(stderr, "gigrf: Line-%d invalid\n", i+3); exit(1); }
        for (m=2; m<l; m++) {
            line += n;
            if (sscanf(line, "%*lf%n",&n) == EOF)
                { fprintf(stderr, "gigrf: Line-%d short\n", i+3); exit(1); }
        }
        line += n;
        if (sscanf(line, "%lf%lf",&cb[i],&cv[i]) != 2)
            { fprintf(stderr, "gigrf: Line-%d short\n", i+3); exit(1); }
    }
    if (l == ncol) tzero = yr2;
    else {
        tzero = yr1; yr2 -= yr1;
        for (i=0; i<nlin; i++) cv[i] = (cv[i]-cb[i])/yr2;
    }
    k = 0;
    for (i=0, n=1; n<=maxod; n++) {
        vgh[0][n]=cb[i]; vght[0][n]=cv[i]; i++;
        if ((cb[i]!=0.) || (cv[i]!=0.)) k = n;
        for (m=1; m<=n; m++) {
            vgh[m][n]=cb[i]; vght[m][n]=cv[i]; i++;
            if ((cb[i]!=0.) || (cv[i]!=0.)) k = n;
            vgh[n][m-1]=cb[i]; vght[n][m-1]=cv[i]; i++;
            if ((cb[i]!=0.) || (cv[i]!=0.)) k = n;
        }
    }
    maxod = k;
    field(6378.137, 298.25722, 6371.2, maxod);
    tcoef(vgh, vght, tzero, 0, dmy); tyear(year);
}

void igrfc(double fido, double fkeido, double hght, double *tf)
{   double fx, fy, fz;
    mfldg(fido, fkeido, hght/1000., &fx, &fy, &fz, tf);
}



//磁気要素に変換
//Convert to magnetic element
void igrfm(double fm[6])
{   double gx, gy, gz, h, dip, dec;
    gcomp(&gx, &gy, &gz);
    h=sqrt(gx*gx+gy*gy); dip=atan2(gz, h); dec=atan2(gy, gx);
    fm[0]=gx; fm[1]=gy; fm[2]=gz; fm[3]=h; fm[4]=dip*RAD; fm[5]=dec*RAD;
}

/*---------------------------------*/
/*   Coefficients setup Routines   */
/*---------------------------------*/

static float rf[7][120] = {
        { -30339., -2123.,  5758.,
           -1654.,  2994., -2006.,  1567.,   130.,  1297., -2036.,
          -403., 1289., 242., 843.,-176., 958., 805., 149., 492.,-280.,
          -392.,   8., 256.,-265.,-223., 357.,  16., 246., 125., -26.,
          -123.,-161.,-107., -51.,  77.,  47.,  60., -14.,   4., 106.,
          -229.,  68.,   3., -32.,  -4., -10.,-112., -13.,  71., -54.,
           -57.,   0., -27.,  12.,  -8., -25.,   9.,  -9.,  23.,  13.,
           -19.,  -2., -17.,  10.,   9.,   3.,  -3., -13., -12.,   5.,
            -4., -17.,   7.,   4.,  -5.,  22.,  12.,  -3.,   6., -16.,
         0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,
         0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.},
        { -30186., -2036.,  5735.,
           -1898.,  2997., -2124.,  1551.,   -37.,  1299., -2144.,
          -361., 1296., 249., 805.,-253., 951., 807., 148., 462.,-264.,
          -393.,  37., 235.,-307.,-204., 368.,  39., 275., 142., -20.,
          -147.,-161., -99., -38.,  74.,  46.,  57., -23.,  15., 102.,
          -210.,  88.,  -1., -43.,  -8.,  -9.,-114.,  -4.,  66., -57.,
           -68.,  -7., -24.,   7.,  -4., -22.,  11.,  -9.,  27.,  11.,
           -17.,  -8., -14.,  11.,  13.,   4.,   3., -15., -12.,   2.,
            -4., -19.,   6.,   1.,  -2.,  18.,   9.,  -6.,   1., -19.,
         0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,
         0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.},
        { -29988., -1957.,  5606.,
           -1997.,  3028., -2129.,  1662.,  -199.,  1279., -2181.,
          -335., 1251., 271., 833.,-252., 938., 783., 212., 398.,-257.,
          -419.,  53., 199.,-298.,-219., 357.,  46., 261., 149., -74.,
          -150.,-162., -78., -48.,  92.,  49.,  65., -15.,  42.,  93.,
          -192.,  71.,   4., -43.,  14.,  -2.,-108.,  17.,  70., -59.,
           -83.,   2., -28.,  20.,  -5., -13.,  16.,   1.,  18.,  11.,
           -23.,  -2., -10.,  20.,   7.,   7.,   1., -18., -11.,   4.,
            -7., -22.,   4.,   9.,   3.,  16.,   7., -13.,  -1., -15.,
             6.,  11., -21.,   2.,  16., -12.,   9.,   9.,  -5.,  -3.,
            -7.,  -1.,   9.,   7.,  10.,   1.,  -6.,  -5.,   2.,  -3.,
            -4.,   1.,   2.,   1.,  -5.,   2.,  -2.,   5.,   5.,  -4.,
             3.,  -1.,   1.,  -2.,   2.,   4.,   3.,  -1.,   0.,  -6.},
        { -29877., -1903.,  5497.,
           -2073.,  3045., -2191.,  1691.,  -309.,  1300., -2208.,
          -312., 1244., 284., 835.,-296., 937., 780., 233., 363.,-250.,
          -426.,  68., 169.,-298.,-215., 356.,  47., 253., 148., -94.,
          -155.,-161., -75., -48.,  95.,  52.,  65., -16.,  50.,  90.,
          -186.,  69.,   4., -50.,  17.,  -4.,-102.,  20.,  75., -61.,
           -82.,   2., -26.,  24.,  -1.,  -6.,  23.,   4.,  17.,   9.,
           -21.,   0.,  -6.,  21.,   6.,   7.,   0., -21., -11.,   5.,
            -9., -25.,   2.,  11.,   4.,  12.,   4., -16.,  -6., -10.,
             5.,  10., -21.,   1.,  16., -12.,   9.,   9.,  -5.,  -3.,
            -6.,  -1.,   9.,   7.,  10.,   2.,  -6.,  -5.,   2.,  -4.,
            -4.,   1.,   2.,   0.,  -5.,   3.,  -2.,   6.,   5.,  -4.,
             3.,   0.,   1.,  -1.,   2.,   4.,   3.,   0.,   0.,  -6.},
        { -29775., -1851.,  5411.,
           -2136.,  3058., -2278.,  1693.,  -380.,  1315., -2240.,
          -287., 1246., 293., 807.,-348., 939., 782., 248., 324.,-240.,
          -423.,  87., 142.,-299.,-211., 353.,  47., 244., 153.,-111.,
          -154.,-166., -69., -37.,  98.,  61.,  64., -16.,  60.,  83.,
          -178.,  68.,   2., -52.,  17.,   2., -96.,  27.,  77., -64.,
           -81.,   4., -27.,  28.,   1.,   1.,  20.,   6.,  16.,  10.,
           -23.,   0.,  -5.,  22.,   5.,  10.,  -1., -20., -11.,   7.,
           -12., -22.,   4.,  12.,   4.,  11.,   3., -16.,  -6., -11.,
             4.,  10., -21.,   1.,  15., -12.,  10.,   9.,  -6.,  -4.,
            -6.,  -1.,   9.,   7.,   9.,   2.,  -7.,  -6.,   2.,  -4.,
            -4.,   1.,   2.,   0.,  -5.,   3.,  -2.,   6.,   4.,  -4.,
             3.,   0.,   1.,  -1.,   2.,   4.,   3.,   0.,   0.,  -6.},
        { -29682., -1789.,  5318.,
           -2197.,  3074., -2356.,  1685.,  -425.,  1329., -2268.,
          -263., 1249., 302., 769.,-406., 941., 782., 262., 291.,-232.,
          -421.,  98., 116.,-301.,-210., 352.,  44., 237., 157.,-122.,
          -152.,-167., -64., -26.,  99.,  66.,  64., -16.,  65.,  77.,
          -172.,  67.,   2., -57.,  17.,   4., -94.,  28.,  78., -67.,
           -77.,   1., -25.,  29.,   3.,   4.,  22.,   8.,  16.,  10.,
           -23.,  -2.,  -3.,  24.,   4.,  12.,  -1., -20.,  -9.,   7.,
           -14., -21.,   4.,  12.,   5.,  10.,   0., -17.,  -7., -10.,
             4.,   9., -19.,   1.,  15., -12.,  11.,   9.,  -7.,  -4.,
            -7.,  -2.,   9.,   7.,   7.,   0.,  -8.,  -6.,   1.,  -3.,
            -4.,   2.,   2.,   1.,  -5.,   3.,  -2.,   6.,   4.,  -4.,
             3.,   0.,   1.,  -2.,   3.,   3.,   3.,  -1.,   0.,  -6.},
        { -29615., -1728.,  5186.,
           -2267.,  3072., -2478.,  1672.,  -458.,  1341., -2290.,
          -227., 1253., 296., 715.,-492., 935., 787., 272., 251.,-232.,
          -405., 119., 110.,-304.,-217., 351.,  44., 222., 172.,-131.,
          -134.,-169., -40., -12., 107.,  72.,  68., -17.,  74.,  64.,
          -161.,  65.,  -5., -61.,  17.,   1., -91.,  44.,  79., -74.,
           -65.,   0., -24.,  33.,   6.,   9.,  24.,   7.,  15.,   8.,
           -25.,  -2.,  -6.,  25.,   6.,  12.,  -9., -22.,  -8.,   8.,
           -17., -21.,   9.,  15.,   7.,   9.,  -8., -16.,  -7.,  -3.,
             5.,   9., -20.,   3.,  13.,  -8.,  12.,   6.,  -6.,  -9.,
            -8.,  -2.,   9.,   9.,   4.,  -4.,  -8.,  -8.,   5.,  -2.,
            -6.,   1.,   2.,   0.,  -3.,   4.,   0.,   5.,   4.,  -6.,
             1.,  -1.,   2.,  -3.,   4.,   0.,   0.,  -2.,  -1.,  -8.} };
static float sv[7][80] = {
        {  15.3,  8.7, -2.3,-24.4,  0.3,-11.8, -1.6,-16.7,  0.2,-10.8,
            4.2,  0.7,  0.7, -3.8, -7.7, -0.7,  0.2, -0.1, -3.0,  1.6,
           -0.1,  2.9, -2.1, -4.2,  1.9,  1.1,  2.3,  2.9,  1.7,  0.6,
           -2.4,  0.0,  0.8,  1.3, -0.3, -0.1, -0.3, -0.9,  1.1, -0.4,
            1.9,  2.0, -0.4, -1.1, -0.4,  0.1, -0.2,  0.9, -0.5, -0.3,
           -1.1, -0.7,  0.3, -0.5,  0.4,  0.3,  0.2,  0.0,  0.4, -0.2,
            0.2, -0.6,  0.3,  0.1,  0.4,  0.1,  0.6, -0.2,  0.0, -0.3,
            0.0, -0.2, -0.1, -0.3,  0.3, -0.4, -0.3, -0.3, -0.5, -0.3},
        {  25.6, 10.0,-10.2,-24.9,  0.7, -3.0,  4.3,-18.9, -3.8,-10.4,
            6.9, -4.1,  2.5, -4.2, -5.0, -0.2, -2.0,  5.0, -3.9,  0.8,
           -2.1,  1.7, -3.1, -1.0,  0.3, -0.7,  1.2,  1.1,  2.3, -1.6,
           -2.0, -0.5,  1.3,  1.0,  1.1,  0.2,  0.5, -0.5,  2.0, -0.1,
            2.8, -0.2,  0.0, -1.3,  0.9,  0.7, -0.1,  1.7,  0.0,  0.0,
           -1.4,  0.0, -0.1,  0.6,  0.3,  0.9,  0.3,  0.3, -0.7,  0.3,
            0.1, -0.5,  0.8,  0.2,  0.3, -0.2,  0.0, -0.4,  0.2, -0.2,
           -0.4, -0.3, -0.3,  0.4,  0.6, -0.3, -0.3, -0.6, -0.1,  0.3},
        {  22.4, 11.3,-15.9,-18.3,  3.2,-12.7,  7.0,-25.2,  0.0, -6.5,
            0.2, -0.7,  2.7,  1.0, -7.9, -1.4, -1.4,  4.6, -8.2,  1.6,
           -1.8,  2.9, -5.0,  0.4,  1.5,  0.4,  1.8, -0.8, -0.4, -3.3,
            0.0,  0.2,  1.3,  1.4,  2.1,  0.4,  0.0, -0.5,  3.4, -1.4,
            0.8,  0.0,  0.8, -1.6,  0.3,  0.5, -0.1,  0.0, -1.0, -0.8,
           -0.4,  0.4,  0.4,  0.5,  0.2,  1.6,  1.4,  0.1, -0.5,  0.1,
           -0.1,  0.0,  1.1,  0.8, -0.2, -0.1, -0.3, -0.7,  0.3,  0.0,
           -0.8, -0.8, -0.2,  0.2,  0.7,  0.2, -0.3, -1.1,  1.2,  0.8},
        {  23.2, 10.0,-24.5,-13.7,  3.4,-11.5,  7.0,-20.2,  5.1, -4.6,
            5.3, -0.6,  2.3,  0.1,-10.8,  0.1, -0.6,  3.8, -7.8,  2.2,
           -1.4,  2.5, -6.8,  0.9,  1.3,  0.1,  0.1, -1.5, -0.2, -3.2,
           -0.1,  0.1,  0.6, -0.1,  0.0,  1.4, -0.3, -0.4,  1.7, -1.1,
            0.6, -0.8,  0.0, -2.3,  0.9, -0.5,  1.2, -0.1,  0.2, -0.6,
            0.2, -0.5,  1.0,  0.8,  1.1,  1.0,  1.9,  0.4,  0.3, -0.5,
            0.2, -0.1,  0.9,  0.7,  0.0,  0.1,  0.3, -1.0,  0.4,  0.1,
           -0.3, -0.8, -0.3,  0.2,  0.1, -0.8, -0.5, -0.1, -0.8,  1.3},
        {  18.0, 10.6,-16.1,-12.9,  2.4,-15.8,  0.0,-13.8,  3.3, -6.7,
            4.4,  0.1,  1.6, -5.9,-10.6,  0.5,  0.6,  2.6, -7.0,  1.8,
            0.5,  3.1, -5.5, -1.4,  0.6, -0.1, -0.1, -1.6,  0.5, -3.1,
            0.4, -0.1,  1.7,  2.3,  0.4,  1.3, -0.2,  0.2,  1.8, -1.3,
            1.3,  0.0, -0.2, -0.9,  0.1,  0.5,  1.2,  1.2,  0.6, -0.5,
            0.6, -0.3,  0.2,  0.6,  0.8,  1.6, -0.5,  0.2, -0.2,  0.2,
            0.0,  0.3,  0.0,  0.2, -0.7,  0.5, -0.2, -0.2,  0.1,  0.3,
           -1.1,  0.3,  0.0,  0.4, -0.1, -0.5, -0.5, -0.3, -0.6,  0.6},
        {  17.6, 13.0,-18.3,-13.2,  3.7,-15.0, -0.8, -8.8,  1.5, -6.4,
            4.1, -0.2,  2.2, -8.1,-12.1,  0.8,  0.9,  1.8, -6.9,  1.2,
            0.5,  2.7, -4.6, -1.0,  0.8,  0.1,  0.2, -1.5,  1.2, -2.0,
            0.3, -0.1,  1.8,  2.3,  0.9,  0.5, -0.4,  0.3,  0.6, -1.6,
            1.9, -0.2, -0.2, -0.9, -0.2,  1.0,  0.0,  2.2, -0.2, -0.8,
            0.8, -0.6,  0.2,  0.6,  0.6,  1.2, -0.4,  0.1,  0.0,  0.2,
           -0.3, -0.6,  0.0,  0.3, -0.2,  0.4,  0.1, -0.2,  0.4,  0.2,
           -1.1,  0.7,  0.3,  0.0,  0.2, -1.2, -0.9, -0.7, -0.3, -0.6},
        {  14.6, 10.7,-22.5,-12.4,  1.1,-20.6, -1.1, -9.6,  0.7, -5.4,
            6.0,  0.9, -0.1, -7.7,-14.2, -1.3,  1.6,  2.1, -7.3,  1.3,
            2.9,  5.0, -3.2,  0.3,  0.0, -0.7, -0.1, -2.1,  0.6, -2.8,
            1.7, -0.8,  1.9,  2.5,  0.1,  1.0, -0.4, -0.2,  0.9, -1.4,
            2.0,  0.0, -0.6, -0.8, -0.3,  0.0,  1.2,  0.9, -0.4, -0.4,
            1.1, -0.3,  0.0,  1.1,  0.3,  1.1, -0.1, -0.2, -0.6,  0.6,
           -0.7, -0.9,  0.2, -0.3,  0.2,  0.1, -0.3,  0.0,  0.4,  0.0,
           -1.0,  0.3,  0.3,  0.6, -0.5, -0.4, -0.7,  0.3, -0.4,  0.7} };
static float df[10][120] = {
        { -30594., -2285.,  5810.,
           -1244.,  2990., -1702.,  1578.,   477.,  1282., -1834.,
          -499., 1255., 186., 913., -11., 944., 776., 144., 544.,-276.,
          -421., -55., 304.,-178.,-253., 346., -12., 194.,  95., -20.,
           -67.,-142.,-119., -82.,  82.,  59.,  57.,   6.,   6., 100.,
          -246.,  16., -25.,  -9.,  21., -16.,-104., -39.,  70., -40.,
           -45.,   0., -18.,   0.,   2., -29.,   6., -10.,  28.,  15.,
           -17.,  29., -22.,  13.,   7.,  12.,  -8., -21.,  -5., -12.,
             9.,  -7.,   7.,   2., -10.,  18.,   7.,   3.,   2., -11.,
             5., -21., -27.,   1.,  17., -11.,  29.,   3.,  -9.,  16.,
             4.,  -3.,   9.,  -4.,   6.,  -3.,   1.,  -4.,   8.,  -3.,
            11.,   5.,   1.,   1.,   2., -20.,  -5.,  -1.,  -1.,  -6.,
             8.,   6.,  -1.,  -4.,  -3.,  -2.,   5.,   0.,  -2.,  -2.},
        { -30554., -2250.,  5815.,
           -1341.,  2998., -1810.,  1576.,   381.,  1297., -1889.,
          -476., 1274., 206., 896., -46., 954., 792., 136., 528.,-278.,
          -408., -37., 303.,-210.,-240., 349.,   3., 211., 103., -20.,
           -87.,-147.,-122., -76.,  80.,  54.,  57.,  -1.,   4.,  99.,
          -247.,  33., -16., -12.,  12., -12.,-105., -30.,  65., -55.,
           -35.,   2., -17.,   1.,   0., -40.,  10.,  -7.,  36.,   5.,
           -18.,  19., -16.,  22.,  15.,   5.,  -4., -22.,  -1.,   0.,
            11., -21.,  15.,  -8., -13.,  17.,   5.,  -4.,  -1., -17.,
             3.,  -7., -24.,  -1.,  19., -25.,  12.,  10.,   2.,   5.,
             2.,  -5.,   8.,  -2.,   8.,   3., -11.,   8.,  -7.,  -8.,
             4.,  13.,  -1.,  -2.,  13., -10.,  -4.,   2.,   4.,  -3.,
            12.,   6.,   3.,  -3.,   2.,   6.,  10.,  11.,   3.,   8.},
        { -30500., -2215.,  5820.,
           -1440.,  3003., -1898.,  1581.,   291.,  1302., -1944.,
          -462., 1288., 216., 882., -83., 958., 796., 133., 510.,-274.,
          -397., -23., 290.,-230.,-229., 360.,  15., 230., 110., -23.,
           -98.,-152.,-121., -69.,  78.,  47.,  57.,  -9.,   3.,  96.,
          -247.,  48.,  -8., -16.,   7., -12.,-107., -24.,  65., -56.,
           -50.,   2., -24.,  10.,  -4., -32.,   8., -11.,  28.,   9.,
           -20.,  18., -18.,  11.,   9.,  10.,  -6., -15., -14.,   5.,
             6., -23.,  10.,   3.,  -7.,  23.,   6.,  -4.,   9., -13.,
             4.,   9., -11.,  -4.,  12.,  -5.,   7.,   2.,   6.,   4.,
            -2.,   1.,  10.,   2.,   7.,   2.,  -6.,   5.,   5.,  -3.,
            -5.,  -4.,  -1.,   0.,   2.,  -8.,  -3.,  -2.,   7.,  -4.,
             4.,   1.,  -2.,  -3.,   6.,   7.,  -2.,  -1.,   0.,  -3.},
        { -30421., -2169.,  5791.,
           -1555.,  3002., -1967.,  1590.,   206.,  1302., -1992.,
          -414., 1289., 224., 878.,-130., 957., 800., 135., 504.,-278.,
          -394.,   3., 269.,-255.,-222., 362.,  16., 242., 125., -26.,
          -117.,-156.,-114., -63.,  81.,  46.,  58., -10.,   1.,  99.,
          -237.,  60.,  -1., -20.,  -2., -11.,-113., -17.,  67., -56.,
           -55.,   5., -28.,  15.,  -6., -32.,   7.,  -7.,  23.,  17.,
           -18.,   8., -17.,  15.,   6.,  11.,  -4., -14., -11.,   7.,
             2., -18.,  10.,   4.,  -5.,  23.,  10.,   1.,   8., -20.,
             4.,   6., -18.,   0.,  12.,  -9.,   2.,   1.,   0.,   4.,
            -3.,  -1.,   9.,  -2.,   8.,   3.,   0.,  -1.,   5.,   1.,
            -3.,   4.,   4.,   1.,   0.,   0.,  -1.,   2.,   4.,  -5.,
             6.,   1.,   1.,  -1.,  -1.,   6.,   2.,   0.,   0.,  -7.},
        { -30334., -2119.,  5776.,
           -1662.,  2997., -2016.,  1594.,   114.,  1297., -2038.,
          -404., 1292., 240., 856.,-165., 957., 804., 148., 479.,-269.,
          -390.,  13., 252.,-269.,-219., 358.,  19., 254., 128., -31.,
          -126.,-157., -97., -62.,  81.,  45.,  61., -11.,   8., 100.,
          -228.,  68.,   4., -32.,   1.,  -8.,-111.,  -7.,  75., -57.,
           -61.,   4., -27.,  13.,  -2., -26.,   6.,  -6.,  26.,  13.,
           -23.,   1., -12.,  13.,   5.,   7.,  -4., -12., -14.,   9.,
             0., -16.,   8.,   4.,  -1.,  24.,  11.,  -3.,   4., -17.,
             8.,  10., -22.,   2.,  15., -13.,   7.,  10.,  -4.,  -1.,
            -5.,  -1.,  10.,   5.,  10.,   1.,  -4.,  -2.,   1.,  -2.,
            -3.,   2.,   2.,   1.,  -5.,   2.,  -2.,   6.,   4.,  -4.,
             4.,   0.,   0.,  -2.,   2.,   3.,   2.,   0.,   0.,  -6.},
        { -30220., -2068.,  5737.,
           -1781.,  3000., -2047.,  1611.,    25.,  1287., -2091.,
          -366., 1278., 251., 838.,-196., 952., 800., 167., 461.,-266.,
          -395.,  26., 234.,-279.,-216., 359.,  26., 262., 139., -42.,
          -139.,-160., -91., -56.,  83.,  43.,  64., -12.,  15., 100.,
          -212.,  72.,   2., -37.,   3.,  -6.,-112.,   1.,  72., -57.,
           -70.,   1., -27.,  14.,  -4., -22.,   8.,  -2.,  23.,  13.,
           -23.,  -2., -11.,  14.,   6.,   7.,  -2., -15., -13.,   6.,
            -3., -17.,   5.,   6.,   0.,  21.,  11.,  -6.,   3., -16.,
             8.,  10., -21.,   2.,  16., -12.,   6.,  10.,  -4.,  -1.,
            -5.,   0.,  10.,   3.,  11.,   1.,  -2.,  -1.,   1.,  -3.,
            -3.,   1.,   2.,   1.,  -5.,   3.,  -1.,   4.,   6.,  -4.,
             4.,   0.,   1.,  -1.,   0.,   3.,   3.,   1.,  -1.,  -4.},
        { -30100., -2013.,  5675.,
           -1902.,  3010., -2067.,  1632.,   -68.,  1276., -2144.,
          -333., 1260., 262., 830.,-223., 946., 791., 191., 438.,-265.,
          -405.,  39., 216.,-288.,-218., 356.,  31., 264., 148., -59.,
          -152.,-159., -83., -49.,  88.,  45.,  66., -13.,  28.,  99.,
          -198.,  75.,   1., -41.,   6.,  -4.,-111.,  11.,  71., -56.,
           -77.,   1., -26.,  16.,  -5., -14.,  10.,   0.,  22.,  12.,
           -23.,  -5., -12.,  14.,   6.,   6.,  -1., -16., -12.,   4.,
            -8., -19.,   4.,   6.,   0.,  18.,  10., -10.,   1., -17.,
             7.,  10., -21.,   2.,  16., -12.,   7.,  10.,  -4.,  -1.,
            -5.,  -1.,  10.,   4.,  11.,   1.,  -3.,  -2.,   1.,  -3.,
            -3.,   1.,   2.,   1.,  -5.,   3.,  -2.,   4.,   5.,  -4.,
             4.,  -1.,   1.,  -1.,   0.,   3.,   3.,   1.,  -1.,  -5.},
        { -29992., -1956.,  5604.,
           -1997.,  3027., -2129.,  1663.,  -200.,  1281., -2180.,
          -336., 1251., 271., 833.,-252., 938., 782., 212., 398.,-257.,
          -419.,  53., 199.,-297.,-218., 357.,  46., 261., 150., -74.,
          -151.,-162., -78., -48.,  92.,  48.,  66., -15.,  42.,  93.,
          -192.,  71.,   4., -43.,  14.,  -2.,-108.,  17.,  72., -59.,
           -82.,   2., -27.,  21.,  -5., -12.,  16.,   1.,  18.,  11.,
           -23.,  -2., -10.,  18.,   6.,   7.,   0., -18., -11.,   4.,
            -7., -22.,   4.,   9.,   3.,  16.,   6., -13.,  -1., -15.,
             5.,  10., -21.,   1.,  16., -12.,   9.,   9.,  -5.,  -3.,
            -6.,  -1.,   9.,   7.,  10.,   2.,  -6.,  -5.,   2.,  -4.,
            -4.,   1.,   2.,   0.,  -5.,   3.,  -2.,   6.,   5.,  -4.,
             3.,   0.,   1.,  -1.,   2.,   4.,   3.,   0.,   0.,  -6.},
        { -29873., -1905.,  5500.,
           -2072.,  3044., -2197.,  1687.,  -306.,  1296., -2208.,
          -310., 1247., 284., 829.,-297., 936., 780., 232., 361.,-249.,
          -424.,  69., 170.,-297.,-214., 355.,  47., 253., 150., -93.,
          -154.,-164., -75., -46.,  95.,  53.,  65., -16.,  51.,  88.,
          -185.,  69.,   4., -48.,  16.,  -1.,-102.,  21.,  74., -62.,
           -83.,   3., -27.,  24.,  -2.,  -6.,  20.,   4.,  17.,  10.,
           -23.,   0.,  -7.,  21.,   6.,   8.,   0., -19., -11.,   5.,
            -9., -23.,   4.,  11.,   4.,  14.,   4., -15.,  -4., -11.,
             5.,  10., -21.,   1.,  15., -12.,   9.,   9.,  -6.,  -3.,
            -6.,  -1.,   9.,   7.,   9.,   1.,  -7.,  -5.,   2.,  -4.,
            -4.,   1.,   3.,   0.,  -5.,   3.,  -2.,   6.,   5.,  -4.,
             3.,   0.,   1.,  -1.,   2.,   4.,   3.,   0.,   0.,  -6.},
        { -29775., -1848.,  5406.,
           -2131.,  3059., -2279.,  1686.,  -373.,  1314., -2239.,
          -284., 1248., 293., 802.,-352., 939., 780., 247., 325.,-240.,
          -423.,  84., 141.,-299.,-214., 353.,  46., 245., 154.,-109.,
          -153.,-165., -69., -36.,  97.,  61.,  65., -16.,  59.,  82.,
          -178.,  69.,   3., -52.,  18.,   1., -96.,  24.,  77., -64.,
           -80.,   2., -26.,  26.,   0.,  -1.,  21.,   5.,  17.,   9.,
           -23.,   0.,  -4.,  23.,   5.,  10.,  -1., -19., -10.,   6.,
           -12., -22.,   3.,  12.,   4.,  12.,   2., -16.,  -6., -10.,
             4.,   9., -20.,   1.,  15., -12.,  11.,   9.,  -7.,  -4.,
            -7.,  -2.,   9.,   7.,   8.,   1.,  -7.,  -6.,   2.,  -3.,
            -4.,   2.,   2.,   1.,  -5.,   3.,  -2.,   6.,   4.,  -4.,
             3.,   0.,   1.,  -2.,   3.,   3.,   3.,  -1.,   0.,  -6.} };

void sigrf(double year)
{   int maxod, i, n, m, l;
    double tzero, dmy[3];
    l=(int)(year-1970.)/5; if (l < 0) l=0; else if (l >= 7) l=6;
    if (l < 2) maxod=8; else maxod=10;
    tzero=(double)(l*5 + 1970); if (l==0) tzero=1965.;
    if ((year<1955.) || (year>2005.))
        fprintf(stderr, "sigrf: IGRF not available for %8.3lf\n", year);
    for (i=0, n=1; n<=maxod; n++) {
        vgh[0][n]=rf[l][i];
        if (n<=8) vght[0][n]=sv[l][i]; else vght[0][n]=0.;
        i++;
        for (m=1; m<=n; m++) {
            vgh[m][n]=rf[l][i];
            if (n<=8) vght[m][n]=sv[l][i]; else vght[m][n]=0.;
            i++;
            vgh[n][m-1]=rf[l][i];
            if (n<=8) vght[n][m-1]=sv[l][i]; else vght[n][m-1]=0.;
            i++;
        }
    }
    field(6378.16, 298.25, 6371.2, maxod);
    tcoef(vgh, vght, tzero, 0, dmy); tyear(year);
}

void sdgrf(double year)
{   int i, n, m, l;
    double dmy[3];
    l=(int)(year-1945.)/5; if (l < 0) l=0; else if (l >= 9) l=8;
    if ((year<1945.) || (year>1990.))
        fprintf(stderr, "sdgrf: DGRF not available for %8.3lf\n", year);
    for (i=0, n=1; n<=10; n++) {
        vgh[0][n]=df[l][i]; vght[0][n]=(df[l+1][i]-df[l][i])/5.; i++;
        for (m=1; m<=n; m++) {
            vgh[m][n]=df[l][i]; vght[m][n]=(df[l+1][i]-df[l][i])/5.; i++;
            vgh[n][m-1]=df[l][i]; vght[n][m-1]=(df[l+1][i]-df[l][i])/5.; i++;
        }
    }
    field(6378.16, 298.25, 6371.2, 10);
    tcoef(vgh, vght, (double)(1945+l*5), 0, dmy); tyear(year);
}

void spgrf(double year)
{   int i, n, m, l;
    double dmy[3];
    l=(int)(year-1945.)/5; if (l < 6) l=6; else if (l >= 10) l=9;
    if ((year<1975.) || (year>1995.))
        fprintf(stderr, "spgrf: PGRF not available for %8.3lf\n", year);
    for (i=0, n=1; n<=10; n++) {
        vgh[0][n]=df[l][i]; vght[0][n]=(rf[l-4][i]-df[l][i])/5.; i++;
        for (m=1; m<=n; m++) {
            vgh[m][n]=df[l][i]; vght[m][n]=(rf[l-4][i]-df[l][i])/5.; i++;
            vgh[n][m-1]=df[l][i]; vght[n][m-1]=(rf[l-4][i]-df[l][i])/5.; i++;
        }
    }
    field(6378.16, 298.25, 6371.2, 10);
    tcoef(vgh, vght, (double)(1945+l*5), 0, dmy); tyear(year);
}

/*------------------------*/
/*   FORTRAN Interfaces   */
/*------------------------*/

/*
void gigrf_(int *gen, float *year) { gigrf(*gen, (double)*year); }
void igrfc_(float *fi, float *fk, float *h, float *f)
    { double df; igrfc((double)*fi,(double)*fk,(double)*h,&df); *f=df; }
void igrfm_(float fm[6])
    { double dfm[6]; int i; igrfm(dfm); for (i=0; i<6; i++) fm[i]=dfm[i]; }
void sigrf_(float *year) { sigrf((double)*year); }
void sdgrf_(float *year) { sdgrf((double)*year); }
void spgrf_(float *year) { spgrf((double)*year); }
*/

/*
int main(void)
{
	double f;
	double fm[6];
	int i, j;
	double temp;

	for(j=0;j<10;j++){
		temp = 2009+0.1*j;
		gigrf(10, temp);
		igrfc(38, 135, 650000,&f);	//Executeはこの中に含む
		igrfm(fm);
		printf("%lf\n", temp);
		for(i=0;i<6;i++){
			printf("fm[%d]=%lf\n", i, fm[i]);
		}
	}

}
*/

//地磁気要素（地心表現）をECI座標へ
//Geomagnetic element (geocentric representation) to ECI coordinates
int TransMagaxisToECI(const double* mag, double* pos, double lonrad, double thetarad, double gmst)
{
	RotationY(mag, pos, 180*DEG2RAD-thetarad);
	RotationZ(pos, pos,-lonrad);
	RotationZ(pos, pos,-gmst);

	return 0;
}

//IGRFの計算を実行するメインルーチン
//Output	:	mag[3]	ECI座標での磁界の値[nT]
//Main routine to execute IGRF calculation
//Output: mag[3] Value of magnetic field in ECI coordinates [nT]
void IgrfCalc(double decyear, double latrad, double lonrad, double alt, double side, double* mag)
{
	static bool first_flg = true;

	double f; 

	if(first_flg==true) {
		gigrf(10, decyear);	//ファイル読み込み File reading
		first_flg = false;
	}
	tyear(decyear);			//実行年の設定 Execution year setting
	igrfc(latrad*RAD2DEG, lonrad*RAD2DEG, alt*1000,&f);	//実行位置の設定&Executeはこの中に含む
	//Execution position setting & Execute is included in this

	mag[0] = x;	//x, y, zはigrf.cppグローバル変数  x, y, z are igrf.cpp global variables
	mag[1] = y;
	mag[2] = z;
	double thetarad = acos(cth); //[0<=theta<=pi?]

	testglobal[0] = mag[0];
	testglobal[1] = mag[1];
	testglobal[2] = mag[2];

	TransMagaxisToECI(mag, mag, lonrad, thetarad, side);

}

} /* end of namespace igrf */