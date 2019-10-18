/*
  digitalWrite(MidIRread, HIGH);
  digitalWrite(Right1IRread, HIGH);
  digitalWrite(Right2IRread, HIGH);
  digitalWrite(Left1IRread, HIGH);
  digitalWrite(Left2IRread, HIGH);
  digitalWrite(FrontIRread, HIGH);
  digitalWrite(RewardIRread, HIGH);
  */
  
  
  while (Midtotal!=3 && L1total!=3 && L2total!=3 && R1total!=3 && R2total!=3 && Fronttotal!=3 && Rewardtotal!=3){
    Midtotal=0;
    L1total=0;
    L2total=0;
    R1total=0;
    R2total=0;
    Fronttotal=0;
    Rewardtotal=0;
    
    for (inc=0; inc < 4 ; inc++ ){
      MidIRvalArray[inc] = analogRead(MidIRread);
      Left1IRvalArray[inc] = analogRead(Left1IRread);
      Left2IRvalArray[inc] = analogRead(Left2IRread);
      Right1IRvalArray[inc] = analogRead(Right1IRread);
      Right2IRvalArray[inc] = analogRead(Right2IRread);
      FrontIRvalArray[inc] = analogRead(FrontIRread);
      RewardIRvalArray[inc] = analogRead(RewardIRread);
      
      if ((inc>0) && MidIRvalArray[inc]==MidIRvalArray[inc-1]){
        Midtotal++;
      }
      if ((inc>0) && Left1IRvalArray[inc]==Left1IRvalArray[inc-1]){
        L1total++;
      }
      if ((inc>0) && Left2IRvalArray[inc]==Left2IRvalArray[inc-1]){
        L2total++;
      }
      if ((inc>0) && Right1IRvalArray[inc]==Right1IRvalArray[inc-1]){
        R1total++;
      }   
      if ((inc>0) && Right2IRvalArray[inc]==Right2IRvalArray[inc-1]){
        R2total++;
      } 
      if ((inc>0) && FrontIRvalArray[inc]==FrontIRvalArray[inc-1]){
        Fronttotal++;
      }  
      if ((inc>0) && RewardIRvalArray[inc]==RewardIRvalArray[inc-1]){
        Rewardtotal++;
      }  
      delay(10);
      Serial.print("\t");
      Serial.print("Mid IR val ");
      Serial.print((long)MidIRvalArray[inc], DEC);
      Serial.print(" & Left1 IR val ");
      Serial.print((long)Left1IRvalArray[inc], DEC);
      Serial.print(" & Left2 IR val ");
      Serial.print((long)Left2IRvalArray[inc], DEC); 
      Serial.print(" & Right1 IR val "); 
      Serial.print((long)Right1IRvalArray[inc], DEC);
      Serial.print(" & Right2 IR val "); 
      Serial.print((long)Right2IRvalArray[inc], DEC);
      Serial.print(" & Front IR val "); 
      Serial.print((long)FrontIRvalArray[inc], DEC);
      Serial.print(" & Reward IR val "); 
      Serial.println((long)RewardIRvalArray[inc], DEC);
    }
  }
  Midbaseline=MidIRvalArray[3];
  L1baseline=Left1IRvalArray[3];
  L2baseline=Left2IRvalArray[3];
  R1baseline=Right1IRvalArray[3];
  R2baseline=Right2IRvalArray[3];
  Frontbaseline=FrontIRvalArray[3];
  Rewardbaseline=RewardIRvalArray[3];
  
  Serial.print("Middle Baseline value is ");
  Serial.print(Midbaseline);
  Serial.print("\t");
  Serial.print("Left 1 Baseline value is ");
  Serial.print(L1baseline);
  Serial.print("\t");
  Serial.print("Left 2 Baseline value is ");
  Serial.print(L2baseline);
  Serial.print("\t");
  Serial.print("and Right 1 Baseline value is ");
  Serial.print(R1baseline);
  Serial.print("\t");
  Serial.print("and Right 2 Baseline value is ");
  Serial.print(R2baseline);
  Serial.print("\t");
  Serial.print(" and Front Baseline value is ");
  Serial.print(Frontbaseline);
  Serial.print("\t");
  Serial.print(" and Reward Baseline value is ");
  Serial.print(Rewardbaseline);
  Serial.print("\t");
  Serial.println("End initialization");
  // tell the PC we are ready
  Serial.println("<Arduino is ready>");
  

}