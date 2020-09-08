/**
 * @file   NJTelemetryHandler.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_tmhandler_NJTelemetryHandler_h
#define stf_core_devicedriver_tmhandler_NJTelemetryHandler_h

#include <fstream>
#include <string>
#include "../../../core/devicedriver/tmhandler/ITelemetryStoragable.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace tmhandler {

template<class T>
class NJTelemetryHandler : virtual public ITelemetryStoragable{
public:
    NJTelemetryHandler(const std::string &filename, bool console_out);
    NJTelemetryHandler();
    virtual ~NJTelemetryHandler();
    void logging(int value, int address);
    virtual void logging(double value, int address);
    virtual void logging(datatype::String value, int address);
    virtual ITelemetryStoragable &operator <<(int value);
    virtual ITelemetryStoragable &operator <<(double value);
    ITelemetryStoragable &operator <<(const char* value);
    virtual ITelemetryStoragable &endl();
 private:
    typename T::OutputFileStream *ofs_;
    bool console_out_;
};

template<class T>
NJTelemetryHandler<T>::NJTelemetryHandler(const std::string &filename, bool console_out)
: console_out_(console_out)
{
	if(filename.length() != 0)
		this->ofs_ = new typename T::OutputFileStream(filename.c_str());
	else
		this->ofs_ = 0;
}

template<class T>
NJTelemetryHandler<T>::NJTelemetryHandler()
: console_out_(true), ofs_(0)
{
	//引数なしの場合は標準出力にのみ表示，ログはとらない
	//When there is no argument, it is displayed only on the standard output and is not logged.
}

template<class T>
NJTelemetryHandler<T>::~NJTelemetryHandler()
{
	if(this->ofs_ != 0) delete this->ofs_;
}

template<class T>
void NJTelemetryHandler<T>::logging(int value, int address)
{
   *this << value;//ロガーは書き込み先アドレスの指定を無視する  
   //Logger ignores destination address specification
}

template<class T>
void NJTelemetryHandler<T>::logging(double value, int address)
{
   *this << value;    
}

template<class T>
void NJTelemetryHandler<T>::logging(datatype::String value, int address)
{
	*this << value.to_char();
}

template<class T>
ITelemetryStoragable &NJTelemetryHandler<T>::operator <<(int value)
{
	if(this->console_out_) util::cout << value << ", ";
	if(this->ofs_ != 0)    *ofs_ << value << ", ";
	return *this;
}

template<class T>
ITelemetryStoragable &NJTelemetryHandler<T>::operator <<(double value)
{
	if(this->console_out_) util::cout << value << ", ";
	if(this->ofs_ != 0)    *ofs_ << value << ", ";
	return *this;
}

template<class T>
ITelemetryStoragable &NJTelemetryHandler<T>::operator <<(const char* value)
{
	if(this->console_out_) util::cout << value << ", ";
	if(this->ofs_ != 0)    *ofs_ << value << ", ";
	return *this;
}

template<class T>
ITelemetryStoragable &NJTelemetryHandler<T>::endl()
{
	if(this->console_out_) util::cout << util::endl;
	if(this->ofs_ != 0)    *ofs_ << util::endl;
	return *this;
}

} /* End of namespace stf::core::devicedriver::tmhandler */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_tmhandler_NJTelemetryHandler_h
