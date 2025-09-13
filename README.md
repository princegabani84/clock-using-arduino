# clock-using-arduino
clock using arduino nano, rtc module 
component used
1. use arduino nano
2. tm1637 4-digit 7 sagment display
3. ds1307 RTC midule
4. 3 pushbuttons

open arduino IDE connect arduino nano to computer 
select tools -> board -> arduino nano
and seclect port connected to arduino nano

goto tools -> namage libraries and doenload libraries 
<img width="1129" height="685" alt="Screenshot 2025-09-13 155344" src="https://github.com/user-attachments/assets/bc87033a-2dcf-46b6-a2b9-258d709260db" />
<img width="1335" height="679" alt="Screenshot 2025-09-13 155122" src="https://github.com/user-attachments/assets/aaa74bf4-5d0b-4a2c-a843-19811db65781" />

connect all components as per circuit diagram
<img width="3000" height="1902" alt="circuit_image" src="https://github.com/user-attachments/assets/f2d0ba82-65d7-4587-838f-db19632bbf7a" />

to set time press set button hour will start blinking by pressing HH button you can adjust hour then press set button hour is set and 
MM will start blinking by pressing MM button you can adjust MM then press button time is set

if power is cut off rtc sets time automatically when power is on

