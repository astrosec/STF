/**
 * @file   DateTimeTest.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef datatype_DateTimeTest_h
#define datatype_DateTimeTest_h


#include <cppunit/extensions/HelperMacros.h>
#include "../DateTime.h"

namespace stf { 
namespace datatype {

class DateTimeTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( DateTimeTest ); // 
	CPPUNIT_TEST( test_init );         // 
	CPPUNIT_TEST( test_add );         // 
	CPPUNIT_TEST( test_totalcount );         // 
	CPPUNIT_TEST_SUITE_END();          // 

public:
	void setUp(){ t_ = new DateTime(); }      // �e�e�X�g�E�P�[�X�̎��s���O�ɌĂ΂��
	void tearDown(){ delete t_; }   // �e�e�X�g�E�P�[�X�̎��s����ɌĂ΂��

protected:
	void test_init();  // 
	void test_add();  // 
	void test_totalcount();

  DateTime* t_;
};

CPPUNIT_TEST_SUITE_REGISTRATION( DateTimeTest ); 

void DateTimeTest::test_init(){
	CPPUNIT_ASSERT_EQUAL(0, t_->minutes());
	CPPUNIT_ASSERT_EQUAL(0, t_->hours());
	CPPUNIT_ASSERT_EQUAL(0, t_->dates());
}

void DateTimeTest::test_add(){
	// �ʏ�n
	t_->add_dates(1);
	t_->add_hours(2);
	t_->add_minutes(3);
	t_->add_seconds(4);
	
	CPPUNIT_ASSERT_EQUAL(1, t_->dates());
	CPPUNIT_ASSERT_EQUAL(2, t_->hours());
	CPPUNIT_ASSERT_EQUAL(3, t_->minutes());
	CPPUNIT_ASSERT_EQUAL(4, t_->seconds());

	t_->clear();

	//seconds�ɂ��J��グ
	t_->add_seconds(3600);
	CPPUNIT_ASSERT_EQUAL(0, t_->seconds());
	CPPUNIT_ASSERT_EQUAL(0, t_->minutes());
	CPPUNIT_ASSERT_EQUAL(1, t_->hours());
	CPPUNIT_ASSERT_EQUAL(0, t_->dates());

	//seconds�ɂ��J�艺��
	t_->add_seconds(-1800);
	CPPUNIT_ASSERT_EQUAL(0, t_->seconds());
	CPPUNIT_ASSERT_EQUAL(30, t_->minutes());
	CPPUNIT_ASSERT_EQUAL(0, t_->hours());
	CPPUNIT_ASSERT_EQUAL(0, t_->dates());

	t_->clear();

	//minutes�ɂ��J��グ
	t_->add_minutes(60 * 24);
	CPPUNIT_ASSERT_EQUAL(0, t_->seconds());
	CPPUNIT_ASSERT_EQUAL(0, t_->minutes());
	CPPUNIT_ASSERT_EQUAL(0, t_->hours());
	CPPUNIT_ASSERT_EQUAL(1, t_->dates());

	//minutes�ɂ��J�艺��
	t_->add_minutes(-60 * 12);
	CPPUNIT_ASSERT_EQUAL(0, t_->seconds());
	CPPUNIT_ASSERT_EQUAL(0, t_->minutes());
	CPPUNIT_ASSERT_EQUAL(12, t_->hours());
	CPPUNIT_ASSERT_EQUAL(0, t_->dates());
}

void DateTimeTest::test_totalcount(){
	t_->add_dates(1);

	CPPUNIT_ASSERT_EQUAL(24, t_->total_hours());
	CPPUNIT_ASSERT_EQUAL(1440, t_->total_minutes());
	CPPUNIT_ASSERT_EQUAL(86400, t_->total_seconds());
}

} /* End of namespace stf::datatype */
} /* End of namespace stf */
#endif // datatype_DateTimeTest_h
