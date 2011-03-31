#include<iostream>
#include<fstream>
#include<vector>

#include "stf/util/Cout.h"
#include "stf/Config.h"
//#include "stf/core/strategy/control/Includes.h"
#include "stf/GlobalObject.h"
#include "stf/InstanceID.h"

#include "stf/core/environment/NullEnv.h"
#include "stf/core/environment/Simulator.h"
#include "stf/core/environment/torquesource/ImpulseNoise.h"
#include "stf/core/environment/torquesource/WhiteNoise.h"

#include "stf/core/mode/ModeBase.h"

#include "stf/core/event/SubjectBase.h"
#include "stf/core/event/Event.h"
#include "stf/core/manager/Includes.h"
#include "stf/core/functor/Functor.h"
#include "stf/core/command/ModeChangeCommand.h"

#include "stf/util/math.h"
#include "stf/util/Trace.h"
#include "stf/core/datapool/Datapool.h"
#include "stf/core/devicedriver/Includes.h"
#include "stf/datatype/IAocsData.h"
#include "stf/datatype/TypeConverter.h"
#include "stf/datatype/Quaternion.h"
#include "stf/datatype/EulerAngle.h"
#include "stf/datatype/DCM.h"
#include "stf/datatype/TypeConverter.h"
#include "stf/datatype/StaticVector.h"
#include "stf/datatype/StaticMatrix.h"
#include "stf/datatype/OrbitCalc.h"
#include "stf/core/datapool/Datapool.h"
#include "stf/core/devicedriver/CDHComponent.h"
#include "stf/util/loki/HierarchyGenerators.h"
#include "stf/core/devicedriver/IOPort.h"
#include "stf/satellite/PRISMFactory.h"
#include "stf/satellite/NJFactory.h"
#include "stf/satellite/SimpleSatelliteFactory.h"
#include "stf/util/math/Exp.h"

#include "stf/core/environment/sh/iodefine.h"
#include "stf/interface/Iterator.h"
#include "stf/satellite/PRISM/PRISMIterator.h"

using namespace stf;
using namespace stf::core;
using namespace stf::core::devicedriver;
using stf::util::cout;
using datatype::TypeConverter;
using namespace stf::core::datapool;

#include <iostream>
#include <list>
int main(void){
	util::Trace::enable(util::Trace::kManager);
	util::Trace::enable(util::Trace::kControlBlock);
	util::Trace::enable(util::Trace::kCommand);
	util::Trace::enable(util::Trace::kEvent);
	util::Trace::enable(util::Trace::kDataPool);

	util::Trace tr(util::Trace::kManager, "man");

	std::cout << "AOCS Framework Test Program:\n\n";

	//stf::factory::SatelliteFactory<ENV>* en = new ();
	stf::core::factory::PRISMFactory<ENV>& factory = stf::core::factory::PRISMFactory<ENV>::getInstance();
	stf::Global<ENV>* gl = factory.create();

	//stf::factory::SatelliteFactory<ENV>* en2 = new stf::factory::NJFactory<ENV>();
	stf::Global<ENV>* gl2 = stf::core::factory::NJFactory<ENV>::getInstance().create();

	//stf::factory::SatelliteFactory<ENV>* en3 = new stf::factory::SimpleSatelliteFactory<ENV>();
	stf::Global<ENV>* gl3 = stf::core::factory::SimpleSatelliteFactory<ENV>::getInstance().create();

	//�V�~�����[�^�̐���
	stf::core::environment::Simulator& s = stf::core::environment::Simulator::get_instance();
	//�V�~�����[�V�����p�̋O�����
	datatype::OrbitInfo orbit(7100000, 0.01, 0, 0.5 * util::math::PI, 0, 0);
	//�V�~�����[�^������
	s.init(gl3, STEPTIME, 100, orbit, new std::ofstream("output.csv"));
	
	//�V�~�����[�^�O���ݒ�
	datatype::StaticVector<3> v;
	v[0] = 0.3;
	v[1] = -0.2;
	s.attachNoiseSource(new stf::core::environment::torquesource::ImpulseNoise(3, v, 0, 3000,&s));
    s.attachNoiseSource(new stf::core::environment::torquesource::WhiteNoise(0.01, 0));

	datatype::List<core::manager::ManagerBase>::iterator it,end;
	end	= gl3->get_function_manager()->end();

	for(it = gl3->get_function_manager()->begin(); it != end; ++it){
		(*it).run();
	}

	//���s�^�X�N�̒ǉ�

	//���̂ق��̐ݒ�
	//g.comm->add_command(new core::command::modeChangeCommand(g.get_global_time(), g.missionmode, g.modeman));
	//g.modeman->change_mode(g.safemode);

	///////////////////////////////////////////////
	// ���s
	for(int i = 0; i < 800; i++)
		s.runOneCycle();

	return 1;
}
