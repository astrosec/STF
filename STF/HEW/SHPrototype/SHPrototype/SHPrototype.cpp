/***********************************************************************/
/*                                                                     */
/*  FILE        :SHPrototype.cpp                                       */
/*  DATE        :Mon, Mar 21, 2011                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :SH7045F                                               */
/*                                                                     */
/*  This file is generated by Renesas Project Generator (Ver.4.18).    */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/***********************************************************************/
                  
#include "../../../stf/datatype/Time.h"
#include "../../../stf/datatype/DCM.h"
#include "../../../stf/datatype/EulerAngle.h"
#include "../../../stf/datatype/Magnetic.h"
#include "../../../stf/datatype/Quaternion.h"
#include "../../../stf/datatype/StaticMatrix.h"
#include "../../../stf/datatype/StaticVector.h"
#include "../../../stf/datatype/Time.h"
#include "../../../stf/datatype/DateTime.h"
#include "../../../stf/datatype/List.h"

//#include "typedefine.h"
#ifdef __cplusplus
//#include <ios>                        // Remove the comment when you use ios
//_SINT ios_base::Init::init_cnt;       // Remove the comment when you use ios
#endif

void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

using namespace stf;

void main(void)
{
	datatype::Time t;
	datatype::DCM d;
	datatype::DateTime dt;
	datatype::List<int> l;
	int i = 0;
	l.add(i);
}

#ifdef __cplusplus
void abort(void)
{

}
#endif