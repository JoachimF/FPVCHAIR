/*typedef struct __attribute__((__packed__)) 
{
   uint8_t  sw_id;
   uint8_t  sw_type;
   uint8_t  sw_middle_b;
   bool sw_val;
   long sw_ts;
   bool sw_tr_state;
}  sw_matrix;
*/

const sw_matrix f16_switch_matrix[] PROGMEM =
  {
  // i  t  m  is  i - id, t - type, m - middle button for types 3 and 4 | sw_type == 1) // regular button | sw_type == 2) // momentary button press on switch flip | sw_type == 3) // selector button switch type 1st button press | 
  //                sw_type == 4) // selector toggle switch type 1st button press | sw_type == 5) // slave button position of switch types 3 and 4
    {1, 4, 10},
    {2, 5, 10},
    {3, 4, 11}, 
    {4, 1, 0},
    {5, 1, 0}
  };

void setup_tqs()
{
  MODE_SWITCH_BUTTON = 30 ;
  Wire.beginTransmission(TQS_I2C_ADDRESS);
  int error = Wire.endTransmission();
  if (error == 0)
  {
    simchair.setThrottleRange(0, 1023);
    simchair.setRxAxisRange(0, 1023);
    dev_tqs = 1;
  }
  for (byte i=0;i<5;i++)
  {
    switch_matrix[i].sw_id = pgm_read_byte(&f16_switch_matrix[i].sw_id);
    switch_matrix[i].sw_type = pgm_read_byte(&f16_switch_matrix[i].sw_type);
    switch_matrix[i].sw_middle_b = pgm_read_byte(&f16_switch_matrix[i].sw_middle_b) - 1;
  }
}

void poll_tqs()
{
  uint16_t throttle, antenna,rx,ry;
  uint8_t b;
  
  Wire.beginTransmission(TQS_I2C_ADDRESS);
  int error = Wire.endTransmission();
  if (error == 0)
  {
    Wire.requestFrom(TQS_I2C_ADDRESS, 10);
    while (Wire.available())
    {
      byte b1 = Wire.read(); // Throttle
      byte b2 = Wire.read();
      byte b3 = Wire.read(); // Antenna
      byte b4 = Wire.read();
      b = Wire.read();
      byte enc = Wire.read();
      byte b5 = Wire.read(); // X hat
      byte b6 = Wire.read();
      byte b7 = Wire.read(); // Y hat
      byte b8 = Wire.read();
      

      e_state[0].val = enc ;
  
      antenna = b3;
      antenna = (antenna << 8) | b4;
      throttle = b1;
      throttle = (throttle << 8) | b2;
      rx = b5;
      rx = (rx << 8) | b6;
      ry = b7;
      ry = (ry << 8) | b8;
    }
  }
    if (TQS_INVERT_TH == 1)
    {
      throttle = 1023 - throttle;
    }
    if (TQS_INVERT_ANT == 1)
    {
      antenna = 1023 - antenna;
    }
    simchair.setThrottle(throttle);
    simchair.setRxAxis(antenna);
    rx = map(rx,0,1023,255,0) ;
    ry = map(ry,0,1023,255,0) ;
    int16_t hat0_val = parse_hat_sw(ry, rx,8);
    simchair.setHatSwitch(0, hat0_val);
    // uncomment next 3 lines for cyclic calibration
    /*Serial.print(throttle);
    Serial.print(" ");
    Serial.print(antenna);
    Serial.print(" ");
    Serial.print(rx);
    Serial.print(" ");
    Serial.print(ry);

    Serial.println() ;*/
    
// parse encoders
  for (byte i = 0; i < 1; i++)
  {

    int e_diff = e_state[i].last_val - e_state[i].val;
    if (((millis() - e_state[i].enc_ts) > 20) && (e_state[i].button_val == 1))
    {
        e_state[i].button_val = 0;
        simchair_aux1.setButton(e_state[i].button_id, 0);
    }
   else if ((e_state[i].last_val != e_state[i].val) && (e_state[i].press_counter == 0))
    {
      if ((e_diff > 1) && (e_diff < 100)) // fast left turn
      {         
        set_button_mode_and_radio_switch_aware(i,1,0);
        e_state[i].enc_ts = millis();
        if (((obs_rate == 1) && (i == 4))|| ((i == 6) && (dg_rate == 1)))  // OBS knob
        {
          e_state[i].press_counter = OBS_HIGH_RATE_BUTTON_PRESSES;
        }
        else
        {
          e_state[i].press_counter = 0;
        }
        e_state[i].last_dir = 0;
        //e_state[i].button_id = i;
        e_state[i].button_val = 1;
        e_state[i].last_val = e_state[i].val;
      }
      else if ((e_diff < -1) && (e_diff > - 100)) // fast right turn
      {
        set_button_mode_and_radio_switch_aware(i,1,1);
        e_state[i].enc_ts = millis();
        if (((obs_rate == 1) && (i == 4))|| ((i == 6) && (dg_rate == 1)))  // OBS knob
        {
          e_state[i].press_counter = OBS_HIGH_RATE_BUTTON_PRESSES;
        }
        else
        {
          e_state[i].press_counter = 0;
        }
        e_state[i].last_dir = 1;
        e_state[i].button_val = 1;
        e_state[i].last_val = e_state[i].val;
      }
      
      else if ((e_diff <= 100) && (e_diff >= 1))// slow left turn
      {
        set_button_mode_and_radio_switch_aware(i,1,0);
        e_state[i].enc_ts = millis();
        e_state[i].press_counter = 0;
        e_state[i].last_dir = 0;
        e_state[i].button_val = 1;
        e_state[i].last_val = e_state[i].val;
      }
      else if ((e_diff >= -100) && (e_diff <= -1)) // slow right turn
      {
        set_button_mode_and_radio_switch_aware(i,1,1);
        e_state[i].enc_ts = millis();
        e_state[i].press_counter = 0;
        e_state[i].last_dir = 1;
        e_state[i].button_val = 1;
        e_state[i].last_val = e_state[i].val;
      }
      else if ((e_diff > 100) || (e_diff < - 100))
      {
        e_state[i].last_val = e_state[i].val;
      }
    }
    else if (((e_state[i].press_counter > 0) && (e_state[i].button_val == 0)) && (millis() - e_state[i].enc_ts > 30))
    {
        set_button_mode_and_radio_switch_aware(i,1,e_state[i].last_dir);
        e_state[i].enc_ts = millis();
        e_state[i].press_counter--;
        e_state[i].button_val = 1;   
        e_state[i].last_val = e_state[i].val;    
    }
  }
    
    // Boutons
   parse_coll_head_sw_matrix(b,0,5) ;
/*   for (byte i = 0; i < 5; i++)
    {
      bool v = (b >> i) & 1;
     
      if (v != TQS_lastButtonState[i]){
*/
/*        if((i == 1) && (v == 0) && TQS_lastButtonState[4] == 0 && rearm1 == true){
          simchair.setButton(4, 1);
          TQS_lastButtonState[4] = 1 ;
          timer1 = millis() ;
          rearm1 = false ;
        //  Serial.println(timer1);
        }
        if(((i == 1) && (v == 1))){
          if(TQS_lastButtonState[4] == 1)
            simchair.setButton(4, 0);
          rearm1 = true ;
          TQS_lastButtonState[4] = 0 ;
         }

*//*        
        simchair.setButton(i, v);
        TQS_lastButtonState[i] = v ;
      }
    }*/
/*    if(timer1 <= (millis()-10000) && TQS_lastButtonState[4] == 1)
    {
          simchair.setButton(4, 0);
          TQS_lastButtonState[4] = 0 ;
   //       Serial.print("timeout1 ");
   //       Serial.print(rearm1);
   //       Serial.println(timer1);
    }
    if(timer2 <= (millis()-1000) && TQS_lastButtonState[5] == 1)
    {
          simchair.setButton(5, 0);
          TQS_lastButtonState[5] = 0 ;
    //      Serial.print("timeout2  ");
          //Serial.print(rearm2);
    //      Serial.println(timer2);
    }
    if((TQS_lastButtonState[0] || TQS_lastButtonState[2]))
    {
      if( TQS_lastButtonState[5] == 1 )
        simchair.setButton(5, 0);
      TQS_lastButtonState[5] = 0 ;
  //    Serial.println("zero");
      rearm2 = true ;
    }
    
    if(rearm2 && (!TQS_lastButtonState[0] && !TQS_lastButtonState[2])) {
        rearm2 = false ;
        simchair.setButton(5, 1);
        TQS_lastButtonState[5] = 1 ;
        timer2 = millis() ;
        //Serial.println(timer2);
      }*/
      
}
