/* *********************************************************************
*********************************************************************
Author: Julien Baglio
E-mail: julien.baglio@cern.ch
Date of Coding: 15/09/2020
pdf luminosities for the DY process p p -> gamma* -> l l up to N3LO QCD
*********************************************************************
********************************************************************* */

// PDG index: d u s c b t
//            1 2 3 4 5 6
//            g
//            21

#include <iostream>
#include <fstream>
#include <cmath>

#include "pdffunctions_w.h"

#include "pdfpar_w.h"

static const double _almost_zero = 1e-12;

// d-ubar luminosity function including the CKM coefficients
double dlumdub(const double x1, const double x2, const double muf2, LHAPDF::PDF const* const pdf)
{
  double res;
  double absckm[7][7];

  if (x1>1.0-_almost_zero or x2>1.0-_almost_zero or x1<_almost_zero or x2<_almost_zero)
    {
      return 0.0;
      std::cout << "warning edges of pdfs!!!" << std::endl;
    }

  absckm[2][1] = 0.97446;
  absckm[1][2] = absckm[2][1];

  absckm[2][3] = 0.22452;
  absckm[3][2] = absckm[2][3];

  absckm[2][5] = 0.00365;
  absckm[5][2] = absckm[2][5];

  absckm[4][1] = 0.22438;
  absckm[1][4] = absckm[4][1];

  absckm[4][3] = 0.97359;
  absckm[3][4] = absckm[4][3];

  absckm[4][5] = 0.04214;
  absckm[5][4] = absckm[4][5];

  absckm[6][1] = 0.00896;
  absckm[1][6] = absckm[6][1];

  absckm[6][3] = 0.04133;
  absckm[3][6] = absckm[6][3];

  absckm[6][5] = 0.999105;
  absckm[5][6] = absckm[6][5];

  res = 0.0;
  for (int i=1;i<6;i = i + 2)
    {
      //:  d ubar + ubar d
      for (int j=2;j<6; j = j + 2)
  	{
	  res +=
	    (pdf->xfxQ2(i*parampdf.wchoice,x1,muf2)  * pdf->xfxQ2(-j*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
	     pdf->xfxQ2(-j*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(i*parampdf.wchoice*parampdf.collidertype,x2,muf2))
	    * absckm[i][j]*absckm[i][j];
  	}
    }
  res = res/x1/x2;
  return res;
}

// d-ubar luminosity function including the CKM coefficients; intended for NNLO and N3LO corrections
double dlumdub2(const double x1, const double x2, const double muf2, LHAPDF::PDF const* const pdf)
{
  double res;
  double absckmud, absckmus, absckmub;
  double absckmcd, absckmcs, absckmcb;
  double absckmtd, absckmts, absckmtb;

  double v2u[2], v2d[3];

  if (x1>1.0-_almost_zero or x2>1.0-_almost_zero or x1<_almost_zero or x2<_almost_zero)
    {
      return 0.0;
      std::cout << "warning edges of pdfs!!!" << std::endl;
    }

  absckmud = 0.97446;  // 21
  absckmus = 0.22452;  // 23
  absckmub = 0.00365;  // 25

  absckmcd = 0.22438;  // 41
  absckmcs = 0.97359;  // 43
  absckmcb = 0.04214;  // 45

  absckmtd = 0.00896;  // 61
  absckmts = 0.04133;  // 63
  absckmtb = 0.999105;  // 65

  v2u[0] = absckmud*absckmud + absckmus*absckmus + absckmub*absckmub;
  v2u[1] = absckmcd*absckmcd + absckmcs*absckmcs + absckmcb*absckmcb;

  v2d[0] = absckmud*absckmud + absckmcd*absckmcd;
  v2d[1] = absckmus*absckmus + absckmcs*absckmcs;
  v2d[2] = absckmub*absckmub + absckmcb*absckmcb;

  res = 0.0;
  for (int i=1;i<6;i = i + 2)
    {
      //:  d ubar + ubar d
      for (int j=2;j<6; j = j + 2)
  	{
  	  res +=
  	    (pdf->xfxQ2(i*parampdf.wchoice,x1,muf2)  * pdf->xfxQ2(-j*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
  	     pdf->xfxQ2(-j*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(i*parampdf.wchoice*parampdf.collidertype,x2,muf2))
  	    * (v2u[(j-2)/2]+v2d[(i-1)/2]);
  	}
    }
  res = res/x1/x2;
  return res;
}


// g-ubar luminosity function including the CKM coefficients
double dlumgub(const double x1, const double x2, const double muf2, LHAPDF::PDF const* const pdf)
{
  double res;
  int j;
  double absckmud, absckmus, absckmub;
  double absckmcd, absckmcs, absckmcb;
  double absckmtd, absckmts, absckmtb;

  double v2u[2], v2d[3];

  if (x1>1.0-_almost_zero or x2>1.0-_almost_zero or x1<_almost_zero or x2<_almost_zero)
    {
      return 0.0;
      std::cout << "warning edges of pdfs!!!" << std::endl;
    }

  absckmud = 0.97446;  // 21
  absckmus = 0.22452;  // 23
  absckmub = 0.00365;  // 25

  absckmcd = 0.22438;  // 41
  absckmcs = 0.97359;  // 43
  absckmcb = 0.04214;  // 45

  absckmtd = 0.00896;  // 61
  absckmts = 0.04133;  // 63
  absckmtb = 0.999105;  // 65

  v2u[0] = absckmud*absckmud + absckmus*absckmus + absckmub*absckmub;
  v2u[1] = absckmcd*absckmcd + absckmcs*absckmcs + absckmcb*absckmcb;

  v2d[0] = absckmud*absckmud + absckmcd*absckmcd;
  v2d[1] = absckmus*absckmus + absckmcs*absckmcs;
  v2d[2] = absckmub*absckmub + absckmcb*absckmcb;

  res = 0.0;
  for (int i=1;i<6;i = i + 2)
    {
      // g-ubar + ubar-g, as well as g-d + d-g
      res +=
	(pdf->xfxQ2(i*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(0,x2,muf2) +
	 pdf->xfxQ2(0,x1,muf2) * pdf->xfxQ2(i*parampdf.wchoice*parampdf.collidertype,x2,muf2))
	* v2d[(i-1)/2];
      if(i<4)
	{
	  j = -(i + 1);
	  res +=
	    (pdf->xfxQ2(0,x1,muf2) * pdf->xfxQ2(j*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
	     pdf->xfxQ2(j*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(0,x2,muf2))
	    * v2u[(i-1)/2];
	}
    }
  res = res/x1/x2;
  return res;
}

// g-ubar luminosity function including the CKM coefficients; intended for N3LO corrections
double dlumgub2(const double x1, const double x2, const double muf2, LHAPDF::PDF const* const pdf)
{
  double res;
  int j;
  double absckmud, absckmus, absckmub;
  double absckmcd, absckmcs, absckmcb;
  double absckmtd, absckmts, absckmtb;

  double v2all;

  if (x1>1.0-_almost_zero or x2>1.0-_almost_zero or x1<_almost_zero or x2<_almost_zero)
    {
      return 0.0;
      std::cout << "warning edges of pdfs!!!" << std::endl;
    }

  absckmud = 0.97446;  // 21
  absckmus = 0.22452;  // 23
  absckmub = 0.00365;  // 25

  absckmcd = 0.22438;  // 41
  absckmcs = 0.97359;  // 43
  absckmcb = 0.04214;  // 45

  absckmtd = 0.00896;  // 61
  absckmts = 0.04133;  // 63
  absckmtb = 0.999105;  // 65

  v2all =
    absckmud*absckmud + absckmus*absckmus + absckmub*absckmub +
    absckmcd*absckmcd + absckmcs*absckmcs + absckmcb*absckmcb;

  res = 0.0;
  for (int i=1;i<6;i = i + 2)
    {
      // g-ubar + ubar-g, as well as g-d + d-g
      res +=
	(pdf->xfxQ2(i*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(0,x2,muf2) +
	 pdf->xfxQ2(0,x1,muf2) * pdf->xfxQ2(i*parampdf.wchoice*parampdf.collidertype,x2,muf2))
	* v2all;
      if(i<4)
	{
	  j = -(i + 1);
	  res +=
	    (pdf->xfxQ2(0,x1,muf2) * pdf->xfxQ2(j*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
	     pdf->xfxQ2(j*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(0,x2,muf2))
	    * v2all;
	}
    }
  res = res/x1/x2;
  return res;
}


// g-u luminosity function including the CKM coefficients
double dlumgu(const double x1, const double x2, const double muf2, LHAPDF::PDF const* const pdf)
{
  double res;
  int j;
  double absckmud, absckmus, absckmub;
  double absckmcd, absckmcs, absckmcb;
  double absckmtd, absckmts, absckmtb;

  double v2u[2], v2d[3];

  if (x1>1.0-_almost_zero or x2>1.0-_almost_zero or x1<_almost_zero or x2<_almost_zero)
    {
      return 0.0;
      std::cout << "warning edges of pdfs!!!" << std::endl;
    }

  absckmud = 0.97446;  // 21
  absckmus = 0.22452;  // 23
  absckmub = 0.00365;  // 25

  absckmcd = 0.22438;  // 41
  absckmcs = 0.97359;  // 43
  absckmcb = 0.04214;  // 45

  absckmtd = 0.00896;  // 61
  absckmts = 0.04133;  // 63
  absckmtb = 0.999105;  // 65

  v2u[0] = absckmud*absckmud + absckmus*absckmus + absckmub*absckmub;
  v2u[1] = absckmcd*absckmcd + absckmcs*absckmcs + absckmcb*absckmcb;

  v2d[0] = absckmud*absckmud + absckmcd*absckmcd;
  v2d[1] = absckmus*absckmus + absckmcs*absckmcs;
  v2d[2] = absckmub*absckmub + absckmcb*absckmcb;

  res = 0.0;
  for (int i=1;i<6;i = i + 2)
    {
      // g-u + u-g, as well as g-dbar + dbar-g
      res +=
	(pdf->xfxQ2(0,x1,muf2) * pdf->xfxQ2(-i*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
	 pdf->xfxQ2(-i*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(0,x2,muf2))
	* v2d[(i-1)/2];
      if(i<4)
	{
	  j = (i + 1);
	  res +=
	    (pdf->xfxQ2(j*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(0,x2,muf2) +
	     pdf->xfxQ2(0,x1,muf2) * pdf->xfxQ2(j*parampdf.wchoice*parampdf.collidertype,x2,muf2))
	    * v2u[(i-1)/2];
	}
    }
  res = res/x1/x2;
  return res;
}

// g-u luminosity function including the CKM coefficients; intended for N3LO corrections
double dlumgu2(const double x1, const double x2, const double muf2, LHAPDF::PDF const* const pdf)
{
  double res;
  int j;
  double absckmud, absckmus, absckmub;
  double absckmcd, absckmcs, absckmcb;
  double absckmtd, absckmts, absckmtb;

  double v2all;

  if (x1>1.0-_almost_zero or x2>1.0-_almost_zero or x1<_almost_zero or x2<_almost_zero)
    {
      return 0.0;
      std::cout << "warning edges of pdfs!!!" << std::endl;
    }

  absckmud = 0.97446;  // 21
  absckmus = 0.22452;  // 23
  absckmub = 0.00365;  // 25

  absckmcd = 0.22438;  // 41
  absckmcs = 0.97359;  // 43
  absckmcb = 0.04214;  // 45

  absckmtd = 0.00896;  // 61
  absckmts = 0.04133;  // 63
  absckmtb = 0.999105;  // 65

  v2all =
    absckmud*absckmud + absckmus*absckmus + absckmub*absckmub +
    absckmcd*absckmcd + absckmcs*absckmcs + absckmcb*absckmcb;

  res = 0.0;
  for (int i=1;i<6;i = i + 2)
    {
      // g-u + u-g, as well as g-dbar + dbar-g
      res +=
	(pdf->xfxQ2(0,x1,muf2) * pdf->xfxQ2(-i*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
	 pdf->xfxQ2(-i*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(0,x2,muf2))
	* v2all;
      if(i<4)
	{
	  j = (i + 1);
	  res +=
	    (pdf->xfxQ2(j*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(0,x2,muf2) +
	     pdf->xfxQ2(0,x1,muf2) * pdf->xfxQ2(j*parampdf.wchoice*parampdf.collidertype,x2,muf2))
	    * v2all;
	}
    }
  res = res/x1/x2;
  return res;
}


// g-g luminosity function including the CKM coefficients
double dlumgg(const double x1, const double x2, const double muf2, LHAPDF::PDF const* const pdf)
{
  double res;

  double absckmud, absckmus, absckmub;
  double absckmcd, absckmcs, absckmcb;
  double absckmtd, absckmts, absckmtb;

  double v2all;

  if (x1>1.0-_almost_zero or x2>1.0-_almost_zero or x1<_almost_zero or x2<_almost_zero)
    {
      return 0.0;
      std::cout << "warning edges of pdfs!!!" << std::endl;
    }

  absckmud = 0.97446;  // 21
  absckmus = 0.22452;  // 23
  absckmub = 0.00365;  // 25

  absckmcd = 0.22438;  // 41
  absckmcs = 0.97359;  // 43
  absckmcb = 0.04214;  // 45

  absckmtd = 0.00896;  // 61
  absckmts = 0.04133;  // 63
  absckmtb = 0.999105;  // 65

  v2all =
    absckmud*absckmud + absckmus*absckmus + absckmub*absckmub +
    absckmcd*absckmcd + absckmcs*absckmcs + absckmcb*absckmcb;

  res = pdf->xfxQ2(0,x1,muf2) * pdf->xfxQ2(0,x2,muf2) * v2all;

  res = res/x1/x2;
  return res;
}


// c-ubar luminosity function including the CKM coefficients
double dlumcub(const double x1, const double x2, const double muf2, LHAPDF::PDF const* const pdf)
{
  double res;
  double absckmud, absckmus, absckmub;
  double absckmcd, absckmcs, absckmcb;
  double absckmtd, absckmts, absckmtb;

  double v2uall;

  if (x1>1.0-_almost_zero or x2>1.0-_almost_zero or x1<_almost_zero or x2<_almost_zero)
    {
      return 0.0;
      std::cout << "warning edges of pdfs!!!" << std::endl;
    }

  absckmud = 0.97446;  // 21
  absckmus = 0.22452;  // 23
  absckmub = 0.00365;  // 25

  absckmcd = 0.22438;  // 41
  absckmcs = 0.97359;  // 43
  absckmcb = 0.04214;  // 45

  absckmtd = 0.00896;  // 61
  absckmts = 0.04133;  // 63
  absckmtb = 0.999105;  // 65

  v2uall = absckmud*absckmud + absckmus*absckmus + absckmub*absckmub;

  res =
    (pdf->xfxQ2(4*parampdf.wchoice,x1,muf2)  * pdf->xfxQ2(-2*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
     pdf->xfxQ2(-2*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(4*parampdf.wchoice*parampdf.collidertype,x2,muf2))*v2uall +
    (pdf->xfxQ2(2*parampdf.wchoice,x1,muf2)  * pdf->xfxQ2(-4*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
     pdf->xfxQ2(-4*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(2*parampdf.wchoice*parampdf.collidertype,x2,muf2))*v2uall;

  res = res/x1/x2;
  return res;
}

// b-dbar luminosity function including the CKM coefficients (included in c-ubar results)
double dlumcub2(const double x1, const double x2, const double muf2, LHAPDF::PDF const* const pdf)
{
  double res;
  double absckmud, absckmus, absckmub;
  double absckmcd, absckmcs, absckmcb;
  double absckmtd, absckmts, absckmtb;

  if (x1>1.0-_almost_zero or x2>1.0-_almost_zero or x1<_almost_zero or x2<_almost_zero)
    {
      return 0.0;
      std::cout << "warning edges of pdfs!!!" << std::endl;
    }

  absckmud = 0.97446;  // 21
  absckmus = 0.22452;  // 23
  absckmub = 0.00365;  // 25

  absckmcd = 0.22438;  // 41
  absckmcs = 0.97359;  // 43
  absckmcb = 0.04214;  // 45

  absckmtd = 0.00896;  // 61
  absckmts = 0.04133;  // 63
  absckmtb = 0.999105;  // 65

  res =
    (pdf->xfxQ2(-3*parampdf.wchoice,x1,muf2)  * pdf->xfxQ2(1*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
     pdf->xfxQ2(1*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(-3*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
     pdf->xfxQ2(-5*parampdf.wchoice,x1,muf2)  * pdf->xfxQ2(1*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
     pdf->xfxQ2(1*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(-5*parampdf.wchoice*parampdf.collidertype,x2,muf2))
    * (absckmud*absckmud + absckmcd*absckmcd) +
    (pdf->xfxQ2(-1*parampdf.wchoice,x1,muf2)  * pdf->xfxQ2(3*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
     pdf->xfxQ2(3*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(-1*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
     pdf->xfxQ2(-5*parampdf.wchoice,x1,muf2)  * pdf->xfxQ2(3*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
     pdf->xfxQ2(3*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(-5*parampdf.wchoice*parampdf.collidertype,x2,muf2))
    * (absckmus*absckmus + absckmcs*absckmcs) +    
    (pdf->xfxQ2(-1*parampdf.wchoice,x1,muf2)  * pdf->xfxQ2(5*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
     pdf->xfxQ2(5*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(-1*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
     pdf->xfxQ2(-3*parampdf.wchoice,x1,muf2)  * pdf->xfxQ2(5*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
     pdf->xfxQ2(5*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(-3*parampdf.wchoice*parampdf.collidertype,x2,muf2))
    * (absckmub*absckmub + absckmcb*absckmcb);
  
  res = res/x1/x2;
  return res;
}


// q-qbar luminosity function including the CKM coefficients
double dlumqqb(const double x1, const double x2, const double muf2, LHAPDF::PDF const* const pdf)
{
  double res;
  double absckmud, absckmus, absckmub;
  double absckmcd, absckmcs, absckmcb;
  double absckmtd, absckmts, absckmtb;

  double v2u[2], v2d[3];

  if (x1>1.0-_almost_zero or x2>1.0-_almost_zero or x1<_almost_zero or x2<_almost_zero)
    {
      return 0.0;
      std::cout << "warning edges of pdfs!!!" << std::endl;
    }

  absckmud = 0.97446;  // 21
  absckmus = 0.22452;  // 23
  absckmub = 0.00365;  // 25

  absckmcd = 0.22438;  // 41
  absckmcs = 0.97359;  // 43
  absckmcb = 0.04214;  // 45

  absckmtd = 0.00896;  // 61
  absckmts = 0.04133;  // 63
  absckmtb = 0.999105;  // 65

  v2u[0] = absckmud*absckmud + absckmus*absckmus + absckmub*absckmub;
  v2u[1] = absckmcd*absckmcd + absckmcs*absckmcs + absckmcb*absckmcb;

  v2d[0] = absckmud*absckmud + absckmcd*absckmcd;
  v2d[1] = absckmus*absckmus + absckmcs*absckmcs;
  v2d[2] = absckmub*absckmub + absckmcb*absckmcb;

  res = 0.0;

  for (int i=1;i<6;i = i + 2)
    {
      res += (pdf->xfxQ2(i*parampdf.wchoice,x1,muf2)  * pdf->xfxQ2(-i*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
	      pdf->xfxQ2(-i*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(i*parampdf.wchoice*parampdf.collidertype,x2,muf2))*v2d[(i-1)/2];
    }
  for (int i=2;i<6;i = i + 2)
    {
      res += (pdf->xfxQ2(i*parampdf.wchoice,x1,muf2)  * pdf->xfxQ2(-i*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
	      pdf->xfxQ2(-i*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(i*parampdf.wchoice*parampdf.collidertype,x2,muf2))*v2u[(i-2)/2];
    }

  res = res/x1/x2;
  return res;
}

// q-qbar luminosity function including the CKM coefficients (sum over all)
double dlumqqb2(const double x1, const double x2, const double muf2, LHAPDF::PDF const* const pdf)
{
  double res;
  double absckmud, absckmus, absckmub;
  double absckmcd, absckmcs, absckmcb;
  double absckmtd, absckmts, absckmtb;

  double v2all;

  if (x1>1.0-_almost_zero or x2>1.0-_almost_zero or x1<_almost_zero or x2<_almost_zero)
    {
      return 0.0;
      std::cout << "warning edges of pdfs!!!" << std::endl;
    }

  absckmud = 0.97446;  // 21
  absckmus = 0.22452;  // 23
  absckmub = 0.00365;  // 25

  absckmcd = 0.22438;  // 41
  absckmcs = 0.97359;  // 43
  absckmcb = 0.04214;  // 45

  absckmtd = 0.00896;  // 61
  absckmts = 0.04133;  // 63
  absckmtb = 0.999105;  // 65

  v2all =
    absckmud*absckmud + absckmus*absckmus + absckmub*absckmub +
    absckmcd*absckmcd + absckmcs*absckmcs + absckmcb*absckmcb;

  res = 0.0;

  for (int i=1;i<6;i++)
    {
      res += (pdf->xfxQ2(i*parampdf.wchoice,x1,muf2)  * pdf->xfxQ2(-i*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
	      pdf->xfxQ2(-i*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(i*parampdf.wchoice*parampdf.collidertype,x2,muf2))*v2all;
    }

  res = res/x1/x2;
  return res;
}


// q-q luminosity function including the CKM coefficients
double dlumqq(const double x1, const double x2, const double muf2, LHAPDF::PDF const* const pdf)
{
  double res;
  double absckmud, absckmus, absckmub;
  double absckmcd, absckmcs, absckmcb;
  double absckmtd, absckmts, absckmtb;

  double v2u[2], v2d[3];

  if (x1>1.0-_almost_zero or x2>1.0-_almost_zero or x1<_almost_zero or x2<_almost_zero)
    {
      return 0.0;
      std::cout << "warning edges of pdfs!!!" << std::endl;
    }

  absckmud = 0.97446;  // 21
  absckmus = 0.22452;  // 23
  absckmub = 0.00365;  // 25

  absckmcd = 0.22438;  // 41
  absckmcs = 0.97359;  // 43
  absckmcb = 0.04214;  // 45

  absckmtd = 0.00896;  // 61
  absckmts = 0.04133;  // 63
  absckmtb = 0.999105;  // 65

  v2u[0] = absckmud*absckmud + absckmus*absckmus + absckmub*absckmub;
  v2u[1] = absckmcd*absckmcd + absckmcs*absckmcs + absckmcb*absckmcb;

  v2d[0] = absckmud*absckmud + absckmcd*absckmcd;
  v2d[1] = absckmus*absckmus + absckmcs*absckmcs;
  v2d[2] = absckmub*absckmub + absckmcb*absckmcb;

  res = 0.0;

  for (int i=1;i<6;i = i + 2)
    {
      res += pdf->xfxQ2(i*parampdf.wchoice,x1,muf2)  * pdf->xfxQ2(i*parampdf.wchoice*parampdf.collidertype,x2,muf2) * v2d[(i-1)/2];
    }
  for (int i=2;i<6;i = i + 2)
    {
      res += pdf->xfxQ2(-i*parampdf.wchoice,x1,muf2)  * pdf->xfxQ2(-i*parampdf.wchoice*parampdf.collidertype,x2,muf2) * v2u[(i-2)/2];
    }

  res = res/x1/x2;
  return res;
}


// q-qprime luminosity function including the CKM coefficients
double dlumqqprime(const double x1, const double x2, const double muf2, LHAPDF::PDF const* const pdf)
{
  double res;
  double absckmud, absckmus, absckmub;
  double absckmcd, absckmcs, absckmcb;
  double absckmtd, absckmts, absckmtb;

  double v2[3][2];

  if (x1>1.0-_almost_zero or x2>1.0-_almost_zero or x1<_almost_zero or x2<_almost_zero)
    {
      return 0.0;
      std::cout << "warning edges of pdfs!!!" << std::endl;
    }

  absckmud = 0.97446;  // 21
  absckmus = 0.22452;  // 23
  absckmub = 0.00365;  // 25

  absckmcd = 0.22438;  // 41
  absckmcs = 0.97359;  // 43
  absckmcb = 0.04214;  // 45

  absckmtd = 0.00896;  // 61
  absckmts = 0.04133;  // 63
  absckmtb = 0.999105;  // 65

  v2[0][0] = absckmud*absckmud;
  v2[1][0] = absckmus*absckmus;
  v2[2][0] = absckmub*absckmub;
  v2[0][1] = absckmcd*absckmcd;
  v2[1][1] = absckmcs*absckmcs;
  v2[2][1] = absckmcb*absckmcb;

  res = 0.0;

  for (int i=1;i<6;i = i + 2)
    {
      for (int j=2; j<6; j = j + 2)
	{
	  res += (pdf->xfxQ2(i*parampdf.wchoice,x1,muf2)  * pdf->xfxQ2(j*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
		  pdf->xfxQ2(j*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(i*parampdf.wchoice*parampdf.collidertype,x2,muf2))*v2[(i-1)/2][(j-2)/2];
	}
    }

  res = res/x1/x2;
  return res;
}

// q-qprime luminosity function including the CKM coefficients (sum over all)
double dlumqqprime2(const double x1, const double x2, const double muf2, LHAPDF::PDF const* const pdf)
{
  double res;
  double absckmud, absckmus, absckmub;
  double absckmcd, absckmcs, absckmcb;
  double absckmtd, absckmts, absckmtb;

  double v2d[3];

  if (x1>1.0-_almost_zero or x2>1.0-_almost_zero or x1<_almost_zero or x2<_almost_zero)
    {
      return 0.0;
      std::cout << "warning edges of pdfs!!!" << std::endl;
    }

  absckmud = 0.97446;  // 21
  absckmus = 0.22452;  // 23
  absckmub = 0.00365;  // 25

  absckmcd = 0.22438;  // 41
  absckmcs = 0.97359;  // 43
  absckmcb = 0.04214;  // 45

  absckmtd = 0.00896;  // 61
  absckmts = 0.04133;  // 63
  absckmtb = 0.999105;  // 65

  v2d[0] = absckmud*absckmud + absckmcd*absckmcd;
  v2d[1] = absckmus*absckmus + absckmcs*absckmcs;
  v2d[2] = absckmub*absckmub + absckmcb*absckmcb;


  res = 0.0;

  for (int i=1;i<6;i = i + 2)
    {
      for (int j=2; j<6; j = j + 2)
	{
	  res += (pdf->xfxQ2(i*parampdf.wchoice,x1,muf2)  * pdf->xfxQ2(j*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
		  pdf->xfxQ2(j*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(i*parampdf.wchoice*parampdf.collidertype,x2,muf2))*v2d[(i-1)/2];
	}
    }

  res = res/x1/x2;
  return res;
}


// qbar-qprimebar luminosity function including the CKM coefficients
double dlumqbqprimeb(const double x1, const double x2, const double muf2, LHAPDF::PDF const* const pdf)
{
  double res;
  double absckmud, absckmus, absckmub;
  double absckmcd, absckmcs, absckmcb;
  double absckmtd, absckmts, absckmtb;

  double v2[3][2];

  if (x1>1.0-_almost_zero or x2>1.0-_almost_zero or x1<_almost_zero or x2<_almost_zero)
    {
      return 0.0;
      std::cout << "warning edges of pdfs!!!" << std::endl;
    }

  absckmud = 0.97446;  // 21
  absckmus = 0.22452;  // 23
  absckmub = 0.00365;  // 25

  absckmcd = 0.22438;  // 41
  absckmcs = 0.97359;  // 43
  absckmcb = 0.04214;  // 45

  absckmtd = 0.00896;  // 61
  absckmts = 0.04133;  // 63
  absckmtb = 0.999105;  // 65

  v2[0][0] = absckmud*absckmud;
  v2[1][0] = absckmus*absckmus;
  v2[2][0] = absckmub*absckmub;
  v2[0][1] = absckmcd*absckmcd;
  v2[1][1] = absckmcs*absckmcs;
  v2[2][1] = absckmcb*absckmcb;

  res = 0.0;

  for (int i=1;i<6;i = i + 2)
    {
      for (int j=2; j<6; j = j + 2)
	{
	  res += (pdf->xfxQ2(-i*parampdf.wchoice,x1,muf2)  * pdf->xfxQ2(-j*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
		  pdf->xfxQ2(-j*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(-i*parampdf.wchoice*parampdf.collidertype,x2,muf2))*v2[(i-1)/2][(j-2)/2];
	}
    }

  res = res/x1/x2;
  return res;
}

// qbar-qprimebar luminosity function including the CKM coefficients (sum over all)
double dlumqbqprimeb2(const double x1, const double x2, const double muf2, LHAPDF::PDF const* const pdf)
{
  double res;
  double absckmud, absckmus, absckmub;
  double absckmcd, absckmcs, absckmcb;
  double absckmtd, absckmts, absckmtb;

  double v2u[2];

  if (x1>1.0-_almost_zero or x2>1.0-_almost_zero or x1<_almost_zero or x2<_almost_zero)
    {
      return 0.0;
      std::cout << "warning edges of pdfs!!!" << std::endl;
    }

  absckmud = 0.97446;  // 21
  absckmus = 0.22452;  // 23
  absckmub = 0.00365;  // 25

  absckmcd = 0.22438;  // 41
  absckmcs = 0.97359;  // 43
  absckmcb = 0.04214;  // 45

  absckmtd = 0.00896;  // 61
  absckmts = 0.04133;  // 63
  absckmtb = 0.999105;  // 65

  v2u[0] = absckmud*absckmud + absckmus*absckmus + absckmub*absckmub;
  v2u[1] = absckmcd*absckmcd + absckmcs*absckmcs + absckmcb*absckmcb;


  res = 0.0;

  for (int i=1;i<6;i = i + 2)
    {
      for (int j=2; j<6; j = j + 2)
	{
	  res += (pdf->xfxQ2(-i*parampdf.wchoice,x1,muf2)  * pdf->xfxQ2(-j*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
		  pdf->xfxQ2(-j*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(-i*parampdf.wchoice*parampdf.collidertype,x2,muf2))*v2u[(j-2)/2];
	}
    }

  res = res/x1/x2;
  return res;
}


// d-s luminosity function including the CKM coefficients
double dlumds(const double x1, const double x2, const double muf2, LHAPDF::PDF const* const pdf)
{
  double res;
  double absckmud, absckmus, absckmub;
  double absckmcd, absckmcs, absckmcb;
  double absckmtd, absckmts, absckmtb;

  double v2d[3];

  if (x1>1.0-_almost_zero or x2>1.0-_almost_zero or x1<_almost_zero or x2<_almost_zero)
    {
      return 0.0;
      std::cout << "warning edges of pdfs!!!" << std::endl;
    }

  absckmud = 0.97446;  // 21
  absckmus = 0.22452;  // 23
  absckmub = 0.00365;  // 25

  absckmcd = 0.22438;  // 41
  absckmcs = 0.97359;  // 43
  absckmcb = 0.04214;  // 45

  absckmtd = 0.00896;  // 61
  absckmts = 0.04133;  // 63
  absckmtb = 0.999105;  // 65

  v2d[0] = absckmud*absckmud + absckmcd*absckmcd;
  v2d[1] = absckmus*absckmus + absckmcs*absckmcs;
  v2d[2] = absckmub*absckmub + absckmcb*absckmcb;


  res = (pdf->xfxQ2(1*parampdf.wchoice,x1,muf2)  * pdf->xfxQ2(3*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
	 pdf->xfxQ2(3*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(1*parampdf.wchoice*parampdf.collidertype,x2,muf2))*(v2d[0]+v2d[1]) +
    (pdf->xfxQ2(1*parampdf.wchoice,x1,muf2)  * pdf->xfxQ2(5*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
     pdf->xfxQ2(5*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(1*parampdf.wchoice*parampdf.collidertype,x2,muf2))*(v2d[0]+v2d[2]) +
    (pdf->xfxQ2(3*parampdf.wchoice,x1,muf2)  * pdf->xfxQ2(5*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
     pdf->xfxQ2(5*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(3*parampdf.wchoice*parampdf.collidertype,x2,muf2))*(v2d[1]+v2d[2]);

  res = res/x1/x2;
  return res;
}

// ubar-cbar luminosity function including the CKM coefficients
double dlumubcb(const double x1, const double x2, const double muf2, LHAPDF::PDF const* const pdf)
{
  double res;
  double absckmud, absckmus, absckmub;
  double absckmcd, absckmcs, absckmcb;
  double absckmtd, absckmts, absckmtb;

  double v2u[2];

  if (x1>1.0-_almost_zero or x2>1.0-_almost_zero or x1<_almost_zero or x2<_almost_zero)
    {
      return 0.0;
      std::cout << "warning edges of pdfs!!!" << std::endl;
    }

  absckmud = 0.97446;  // 21
  absckmus = 0.22452;  // 23
  absckmub = 0.00365;  // 25

  absckmcd = 0.22438;  // 41
  absckmcs = 0.97359;  // 43
  absckmcb = 0.04214;  // 45

  absckmtd = 0.00896;  // 61
  absckmts = 0.04133;  // 63
  absckmtb = 0.999105;  // 65

  v2u[0] = absckmud*absckmud + absckmus*absckmus + absckmub*absckmub;
  v2u[1] = absckmcd*absckmcd + absckmcs*absckmcs + absckmcb*absckmcb;


  res = (pdf->xfxQ2(-2*parampdf.wchoice,x1,muf2)  * pdf->xfxQ2(-4*parampdf.wchoice*parampdf.collidertype,x2,muf2) +
	 pdf->xfxQ2(-4*parampdf.wchoice,x1,muf2) * pdf->xfxQ2(-2*parampdf.wchoice*parampdf.collidertype,x2,muf2))*(v2u[0]+v2u[1]);

  res = res/x1/x2;
  return res;
}
