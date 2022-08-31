// Module:		Utilities
// Author:		Carlos Rodriguez
// Date:		March 9, 2021
// Purpose:		Template functions
//				Useful utilities
//

#pragma once

#define TCHAR_SIZE 128    // standard size of TCHAR arrays

#include <string>         // string library
using namespace std;      // set standard namespace

// converts TCHAR to integer, returns integer
// truncates decimal values
// returns MAXINT if too many characters
// returns 0 if non-digital input
template <class Type>
int TCHAR2Int(Type* szIn)
{
	return _tstoi(szIn);   // convert TCHAR to int
}

// converts integer into a TCHAR
// return value in TCHAR parameter
// assumes radix of 10
template <class Type>
void Int2TCHAR(Type iIn, TCHAR* szIn)
{
	// assumes TCHAR was created using this utility
	_itot_s(iIn, szIn, TCHAR_SIZE, 10);
}

// converts TCHAR to double
// uses the standard utility _tcstod()
// _tcstod()'s 2nd parameter is the return value that
//       points to the 1st char that could not be converted
// returns 0.0 if non-digital input
template <class Type>
double TCHAR2Double(Type* szIn)
{
	return _tcstod(szIn, NULL);         // 2nd parameter not used
}

// converts double to TCHAR
// iPrecision determines the number of decimal places
// returns pointer to local TCHAR
template <class Type>
void Double2TCHAR(Type dIn, TCHAR* szReturn, int iPrecision)
{
	TCHAR szControl[10];			// conversion mask
	TCHAR szWork[TCHAR_SIZE];		// completed TCHAR

	_stprintf_s(szControl,			// create mask conversion
		TEXT("%%.%df"),				// mask template
		iPrecision);				// user specified precision (decimal places)

	_stprintf_s(szWork,				// convert double to TCHAR
		szControl,                  // control string
		dIn);                       // value

	 // copy completed TCHAR to return
	_tcscpy_s(szReturn, TCHAR_SIZE, szWork);
}

// converts string to TCHAR
// returns pointer to local TCHAR
template <class Type>
void String2TCHAR(Type strIn, TCHAR* szIn)
{
	size_t pReturnValue;					// return value for mbstowcs_s
	mbstowcs_s(								// convert cahr array to wide char array
		&pReturnValue,						// error message
		szIn,								// destination TCHAR array
		TCHAR_SIZE,							// size of TCHAR array
		strIn.c_str(),						// source string
		TCHAR_SIZE);						// max # of chars to convert
}

// converts TCHAR to string
// returns string
template <class Type>
string TCHAR2String(Type* szIn)
{
	string strReturn;				// local string to return

	// convert TCHAR to string
	strReturn.assign(				// set the value of a string object
		&szIn[0],					// start of the TCHAR
		&szIn[_tcslen(szIn)]);		// end of the TCHAR

	return strReturn;				// return converted text
}