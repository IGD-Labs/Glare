
#include "../include/emp_core.h"


TEST(GenCumulativeSkyTest, test1) {
    

    EmpModel model = EmpModel();
    Location * l = model.getLocation();
    l->fillWeatherFromEPWFile("../../tests/weather/Oslo.epw");
    genCumulativeSky(&model,false,true,"cumulative.cal");
    
	ASSERT_TRUE(false);

}
