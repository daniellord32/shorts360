//-------------------------------------------------------------------------------
// Check the state of the power
//-------------------------------------------------------------------------------

void power_toggle()
{
	static double prev_pos = 0;

	if (prev_pos != power_on)
	{
		prev_pos = power_on;
		//set the named variable to the new state
		set_named_variable_value(xPowerOn, power_on);
	}
	return;
}