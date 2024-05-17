// Getting angle & Convert from degree to rad
float desired_angle = 0;
float actual_angle = 5; // Example

// PID Gains
float kp = 0;
float ki = 0;
float kd = 0; 

// PID Parameters/Varuables
error_accum = 0;
error_previous = 0;
previous_time = 0;

void setup() {
  
}

void loop() {

  // Defineing error
  error = actual_angle - desired_angle;
  error_accum = error_accum + error;  // enhance the desired value
  error_current = error;
  current_time = millis();

  // Set PID parameters
  p_error = error * kp;
  i_error = error_accum * ki;
  d_error = (error_current - error_previous) / (current_time - previous_time) * kd;

  // PID output
  pid = p_error + i_error + d_error;

  // Update values
  previous_time = current_time;
  error_previous = error_cuurent;

}
