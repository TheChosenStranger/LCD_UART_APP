
#define SWITCHES_FRAME_ID	0x22
#define SWITCHES_FRAME_LEN  6

#define MIN_SWITCH_NUM		0
#define MAX_SWITCH_NUM		6
 
#define DATE_SWITCH  0b00000001
#define UP_SWITCH    0b00000010
#define DOWN_SWITCH  0b00000100
#define RIGHT_SWITCH 0b00001000
#define LEFT_SWITCH  0b00010000
#define EDIT_SWITCH  0b00100000

#define TIME_MODE 0x01
#define EDIT_MODE 0x02
#define DATE_MODE 0x03

#define PRESSED_SWITCH		1

#define SEC_L_POSITION		11
#define SEC_H_POSITION		10
#define MIN_L_POSITION		8
#define MIN_H_POSITION		7
#define HRS_L_POSITION		5
#define HRS_H_POSITION		4

#define SECS_IN_HOUR		120
#define SECS_IN_MIN	        60

#define ONE_SECOND_COUNTER_RESET 0
#define ONE_SECOND_COUNTER_MAX	 10

#define DATE_LEN		10
#define TIME_LEN 		 8
#define START_TIME     0x3228
#define TEN				10
#define NUM_TO_STRING	'0'

#define MODE_UNCHANGED 		 0
#define MODE_CHANGED_STEP1	 1
#define MODE_CHANGED_STEP2   2

static u32 currentTime = START_TIME;
static u8 currentDate[DATE_LEN] = {'2','5','/','0','4','/','2','0','2','0'};
static u8 watchMode = TIME_MODE;
static u8 changeMode = MODE_UNCHANGED;
static u8 editPosition = MIN_POSITION;

static u8 DisplayTime(u8 timeS);

app2runnable()
{
	static u8 oneSecCounter = ONE_SECOND_COUNTER_RESET;
	u8 receivedFrameData,receivedFrameID,switchCounter,receivedData[SWITCHES_FRAME_LEN];
	/*Receive switches status through UART*/
		HUART_Recieve(receivedData,SWITCHES_FRAME_LEN);
	/*Deconstruct received Frame*/
		FRAMECONST_FrameConstructor(receivedData,receivedFrameID,receivedFrameData);
	/*Action depending on data*/
		/*Check the frame ID*/
		if (SWITCHES_FRAME_ID == receivedFrameID)
		{
			/*Check which switch is pressed*/
			for(switchCounter=MIN_SWITCH_NUM; switchCounter<MAX_SWITCH_NUM;switchCounter++)
			{
				receivedFrameData = receivedFrameData<<switchCounter;
				if (receivedFrameData == PRESSED_SWITCH)
				{
					receivedFrameData = receivedFrameData >> switchCounter;
					break;
				}
			}
			/*Date-Time switch is pressed*/
			if(receivedFrameData == DATE_SWITCH)
			{
				if(watchMode == TIME_MODE)
				{
					watchMode = DATE_MODE;
					changeMode = MODE_CHANGED_STEP2;
				}
				else if(watchMode == DATE_MODE)
				{
					watchMode = TIME_MODE;
					changeMode = MODE_CHANGED_STEP2;
				}
			
			/*Edit switch is pressed*/
			else if(receivedFrameData == EDIT_SWITCH)
			{
				if(watchMode == TIME_MODE)
				{
					watchMode = EDIT_MODE;
					changeMode = MODE_CHANGED_STEP2;
				}
				else if(watchMode == EDIT_SWITCH)
				{
					watchMode = TIME_MODE;
					changeMode = MODE_CHANGED_STEP2;
				}
			}
			/*UP switch is pressed*/
			else if(receivedFrameData == UP_SWITCH)
			{
				if(watchMode == EDIT_SWITCH)
				{
					if(editPosition == HRS_H_POSITION)
						{currentTime+=10*SECS_IN_HOUR;}
					else if (editPosition == HRS_L_POSITION)
						{currentTime+=1*SECS_IN_HOUR;}
					else if(editPosition == MIN_H_POSITION)
						{currentTime+=10*SECS_IN_MIN;}
					else if(editPosition == MIN_L_POSITION)
						{currentTime+=1*SECS_IN_MIN;}
					else if(editPosition == SEC_H_POSITION)
						{currentTime+=10;}
					else if(editPosition == SEC_L_POSITION)
						{currentTime+=1;}
				}
			}
			/*Down switch is pressed*/
			else if(receivedFrameData == Down_SWITCH)
			{
				if(watchMode == EDIT_SWITCH)
				{
					if(editPosition == HRS_H_POSITION)
						{currentTime-=10*SECS_IN_HOUR;}
					else if (editPosition == HRS_L_POSITION)
						{currentTime-=1*SECS_IN_HOUR;}
					else if(editPosition == MIN_H_POSITION)
						{currentTime-=10*SECS_IN_MIN;}
					else if(editPosition == MIN_L_POSITION)
						{currentTime-=1*SECS_IN_MIN;}
					else if(editPosition == SEC_H_POSITION)
						{currentTime-=10;}
					else if(editPosition == SEC_L_POSITION)
						{currentTime-=1;}
				}
			}
			/*RIGHT switch is pressed*/
			else if(receivedFrameData == RIGHT_SWITCH)
			{
				if(watchMode == EDIT_SWITCH)
				{
					if(editPosition == HRS_L_POSITION)
						{editPosition = MIN_H_POSITION;}
					else if (editPosition == MIN_L_POSITION)
						{editPosition = SEC_H_POSITION;}
					else if(editPosition < SEC_L_POSITION)
						{editPosition++;}
				}
			}
			/*UP switch is pressed*/
			else if(receivedFrameData == LEFT_SWITCH)
			{
				if(watchMode == EDIT_SWITCH)
				{
					if(editPosition == MIN_H_POSITION)
						{editPosition = HRS_L_POSITION;}
					else if (editPosition == SEC_H_POSITION)
						{editPosition = MIN_L_POSITION;}
					else if(editPosition > HRS_H_POSITION)
						{editPosition--;}
				}
			}
		}
		/*Check Current mode*/
		if (watchMode == TIME_MODE)
		{
			if(changeMode = MODE_CHANGED_STEP2)
			{
				HLCD_u8WriteCmdRequest(CURSOR_OFF);
				changeMode = MODE_CHANGED_STEP1;
			}
			else if(changeMode = MODE_CHANGED_STEP1)
			{
				HLCD_u8CursorPosition(0,HRS_H_POSITION);
				changeMode = MODE_UNCHANGED;
			}
			else
			{
				DisplayTime(currentTime);
			}
		}
		else if (watchMode == DATE_MODE)
		{
			if(changeMode = MODE_CHANGED_STEP2)
			{
				HLCD_u8CursorPosition(0,HRS_H_POSITION);
				changeMode = MODE_UNCHANGED;
			}
			else
			{
				HLCD_u8WriteDataRequest(currentDate,DATE_LEN);
			}
		}
		if (watchMode == EDIT_SWITCH)
		{
			if(changeMode = MODE_CHANGED_STEP2)
			{
				HLCD_u8CursorPosition(0,editPosition);
				changeMode = MODE_UNCHANGED;
			}
			else
			{
				HLCD_u8WriteCmdRequest(CURSOR_ON);
			}
		}
	/*Increment time every 1 sec*/
	oneSecCounter++;
	if(oneSecCounter == ONE_SECOND_COUNTER_MAX)
	{
		currentTime++;
		oneSecCounter = ONE_SECOND_COUNTER_RESET;
	}
}

static DisplayTime(u32 timeS)
{
	u8 time[TIME_LEN]={' ',0,0,':',0,0,':',0,0,' '};
	/*Calculate hours*/
	time[0] = timeS/SECS_IN_HOUR;
	time[1] = time[0]%TEN + NUM_TO_STRING;
	time[0] = time[0]/TEN + NUM_TO_STRING;
	timeS -= timeS/SECS_IN_HOUR;
	/*Calculate minuts*/
	time[3] = timeS/SECS_IN_MIN;
	time[4] = time[3]%TEN + NUM_TO_STRING;
	time[3] = time[3]/TEN + NUM_TO_STRING;
	timeS -= timeS/SECS_IN_MIN;
	/*Calculate seconds*/
	time[6] = timeS;
	time[7] = time[6]%TEN + NUM_TO_STRING;
	time[6] = time[6]/TEN + NUM_TO_STRING;
	HLCD_u8WriteDataRequest(time,TIME_LEN);
}