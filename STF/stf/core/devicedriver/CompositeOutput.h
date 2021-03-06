/**
 * @file   CompositeOutput.h
 * @brief  AOCSActuatorの集合体を表現するクラス．
 * A class that represents an aggregate of AOCSActuator.
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_CompositeOutput_h
#define stf_core_devicedriver_CompositeOutput_h
#include "../../util/stfassert.h"
#include "AOCSActuator.h"
#include "../datapool/Datapool.h"
#include "DistributionPolicy.h"

namespace stf {
namespace core {
namespace devicedriver {

//! AOCSActuatorの集合体を表すクラス．
/*! 
	@tparam Leaf             纏めるAOCSActuatorの型．
	@tparam Numbers          チャネル数．
	@tparam UseAlignment     取り付け行列に基づいた指令値の分配を行うか
	@tparam DistributionPolicy 分配に使用するポリシークラス．

	Compositeデザインパターンを使うことで，単体のAOCSActuatorと同等の扱いが可能．
	軸ごとに通信系統が独立したアクチュエータを，一個のモジュールのように操作できる．
	@tparam Leaf Type of AOCS Actuator to be put together.
@tparam Numbers Number of channels.
@tparam UseAlignment Whether to distribute command values based on the mounting matrix
@tparam DistributionPolicy Policy class used for distribution.

By using the Composite design pattern, it can be handled in the same way as a single AOCS Actuator.
An actuator with an independent communication system for each axis can be operated like a module.

	@code
	RW rw[4]; //1軸ホイール 4-axis wheel module
	CompositeOutput<RW, 4> rwmodule; //4軸ホイールモジュール
	
	for(int i = 0; i < 4; i ++)
		rwmodule.append_child(rw[i]);//モジュールに子を登録 Register child in module
	
	datatype::StaticVector<3> torque;
	rwmodule.set_torque(torque);//指令値をセット Set command value
	
	rwmodule.do_update();//指令値を子に分配 Distribute command value to children
	@endcode
	
	Compositeから子への分配規則は，DistributionPolicyポリシー・クラスが決定する．
	DistributionPolicyは以下の2つのメソッドを持っている必要がある．
	The distribution policy from Composite to children is determined by the DistributionPolicy policy class.
DistributionPolicy needs to have the following two methods.
	
	:setup:子が既定の個数登録された段階で実行される，ポリシークラスの初期化メソッド．空でも良い．
	:distribute:Compositeの値を子に分配するメソッド．
	
	テンプレート引数を省略した場合，ポリシーはDistributionSelectorメタ関数によって自動的に決定される．
	:setup: Policy class initialization method that is executed when a specified number of children are registered. It can be empty.
Method to distribute :distribute:Composite values to children.
It's a sequel.
If you omit the template argument, the policy is automatically determined by the DistributionSelector metafunction.
*/
template
<
	class Leaf, 
	int Numbers, 
	bool UseAlignment = false, 
	class DistributionPolicy = typename DistributionSelector<typename Leaf::Hold, typename Leaf::Target, Numbers, UseAlignment>::Result 
>
class CompositeOutput : public AOCSActuator<typename Leaf::Environment, typename Leaf::Target, typename Leaf::Target>, public DistributionPolicy {
public:
	STF_STATIC_ASSERT( Numbers <= 255 , CHILD_NUMBER_OVERFLOW );

	typedef AOCSActuator<typename Leaf::Environment, typename Leaf::Target, typename Leaf::Target> Base;
	typedef Leaf Child;
	enum { UseAlignmentForDistribution = UseAlignment, NumberOfChilds = Numbers };

	CompositeOutput(const datatype::DCM& dcm) : Base("Composite", dcm), index_(0)
	{
		for(int i = 0; i < Numbers; i++) childs_[index_] = 0;
	}

	virtual ~CompositeOutput(){}
	virtual void do_update();
	void append_child(Leaf* c);
private:
	Child* childs_[Numbers];
	unsigned char index_;//max 255 childs
};

//! Compositeが纏める子オブジェクトを登録する．Register the child objects that Composite collects.
template <class Leaf, int Numbers, bool UseAlignment, class DistributionPolicy>
void CompositeOutput<Leaf, Numbers, UseAlignment, DistributionPolicy>::append_child(Leaf* c){
	stf_assert(index_ < Numbers);
	childs_[index_] = c;
	index_++;
	if(index_ == Numbers){//子が出そろった All the children
		setup(this, childs_);//Policy Class Method
	}
}

//! 親から子へ再帰的にUpdateを実行する．
//Recursively execute Update from parent to child.
template <class Leaf, int Numbers, bool UseAlignment, class DistributionPolicy>
void CompositeOutput<Leaf, Numbers, UseAlignment, DistributionPolicy>::do_update(){
	if(this->datapool_ != 0){
		this->datapool_->set<CompositeOutput<Leaf, Numbers, UseAlignment, DistributionPolicy> >(datapool_hold_index_, this->output_);//
	}

	distribute(this, childs_); //Policy Class Method

	for(unsigned char i = 0; i < Numbers; ++i){
		if(childs_[i] != 0)
			childs_[i]->do_update();
	}
}

} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_CompositeOutput_h
