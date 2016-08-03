/*
 * agvcmd.h
 *
 *  Created on: Aug 1, 2016
 *      Author: agv
 */

#ifndef AGVCMD_CPP_
#define AGVCMD_CPP_
#include "agvcmdFunction.h"


bool FillCommand(const int LeftWheelPWM, const int RightWheelPWM, ControlPackge & cmdPackage)
      {
           U_uint32_t LeftWheel, RightWheel;

           LeftWheel.value = LeftWheelPWM;
           RightWheel.value = RightWheelPWM;

           cmdPackage.cmd.WheelLeft.bit[0] = LeftWheel.bit[0];
           cmdPackage.cmd.WheelLeft.bit[1] = LeftWheel.bit[1];
           cmdPackage.cmd.WheelLeft.bit[2] = LeftWheel.bit[2];
           cmdPackage.cmd.WheelLeft.bit[3] = LeftWheel.bit[3];
           cmdPackage.cmd.WheelRight.bit[0] = RightWheel.bit[0];
           cmdPackage.cmd.WheelRight.bit[1] = RightWheel.bit[1];
           cmdPackage.cmd.WheelRight.bit[2] = RightWheel.bit[2];
           cmdPackage.cmd.WheelRight.bit[3] = RightWheel.bit[3];

          return true;
      }

bool FillStaticFeedback(HANsFeedbackData &agv)
{
	agv.Data.FrameDataHeader.FrameHeader.bit[0] = 0xAA;
	agv.Data.FrameDataHeader.FrameHeader.bit[1] = 0x55;
	agv.Data.FrameDataHeader.DatasLength = 0x1E;
	agv.Data.SensorsData.MsgHeader = 0x01;
	agv.Data.SensorsData.MsgLength = 0x13;
	agv.Data.SensorsData.Bumper = 0x00;
	agv.Data.SensorsData.WheelMissed = 0x00;
	agv.Data.SensorsData.TouchGround = 0x00;
	agv.Data.SensorsData.PWMLeft = 0x00;
	agv.Data.SensorsData.PWMRight = 0x00;
	agv.Data.SensorsData.HANBattery = 0x00;
	agv.Data.SensorsData.HANButton = 0x00;
	agv.Data.SensorsData.HANCharger = 0x00;
	agv.Data.SensorsData.CurrentBeyond = 0x00;
	agv.Data.Gyromsg.MsgHeader = 0x04;
	agv.Data.Gyromsg.MsgLength = 0x07;
	agv.Data.Gyromsg.NULL1 = 0x00;
	agv.Data.Gyromsg.NULL2 = 0x00;
	agv.Data.Gyromsg.NULL3 = 0x00;
	agv.Data.checksum = 0x00;
	return true;
	}







void FillCmd2Buff(char* write_buff,ControlPackge &Buffer)
	{
		write_buff[0] = Buffer.FrameDataHeader.FrameHeader.bit[0];
		write_buff[1] = Buffer.FrameDataHeader.FrameHeader.bit[1];
		write_buff[2] = Buffer.FrameDataHeader.DatasLength;
		write_buff[3] = Buffer.cmd.DataHeader;
		write_buff[4] = Buffer.cmd.DataLenght;
		write_buff[5] = Buffer.cmd.WheelLeft.bit[0];
		write_buff[6] = Buffer.cmd.WheelLeft.bit[1];
		write_buff[7] = Buffer.cmd.WheelLeft.bit[2];
		write_buff[8] = Buffer.cmd.WheelLeft.bit[3];
		write_buff[9] = Buffer.cmd.WheelRight.bit[0];
		write_buff[10] = Buffer.cmd.WheelRight.bit[1];
		write_buff[11] = Buffer.cmd.WheelRight.bit[2];
		write_buff[12] = Buffer.cmd.WheelRight.bit[3];
		write_buff[13] = Buffer.checksum;
	}

void AppendCmd2Buff(VBytes &send_buf,ControlPackge &cmdpack)
{
	send_buf.resize(sizeof(ControlPackge));
	send_buf.push_back(cmdpack.FrameDataHeader.FrameHeader.bit[0]);
	send_buf.push_back(cmdpack.FrameDataHeader.FrameHeader.bit[1]);
	send_buf.push_back(cmdpack.FrameDataHeader.DatasLength);
	send_buf.push_back(cmdpack.cmd.DataHeader);
	send_buf.push_back(cmdpack.cmd.DataLenght);
	send_buf.push_back(cmdpack.cmd.WheelLeft.bit[0]);
	send_buf.push_back(cmdpack.cmd.WheelLeft.bit[1]);
	send_buf.push_back(cmdpack.cmd.WheelLeft.bit[2]);
	send_buf.push_back(cmdpack.cmd.WheelLeft.bit[3]);
	send_buf.push_back(cmdpack.cmd.WheelRight.bit[0]);
	send_buf.push_back(cmdpack.cmd.WheelRight.bit[1]);
	send_buf.push_back(cmdpack.cmd.WheelRight.bit[2]);
	send_buf.push_back(cmdpack.cmd.WheelRight.bit[3]);
	send_buf.push_back(cmdpack.checksum);
}

void ComputeOdom(int32_t dpluse_l ,int32_t dpluse_r, float_t dt_sec, ODOM &odom_msg)
{
	/*  if (OdometryInitialized)
	  {*/
	float_t dPassPath_L = Cm * dpluse_l;
	//float_t dPassPath_one = Cm * 900.0;
	//std::cout<<"Cm:"<<std::showpoint<<dPassPath_one;
	//std::cout<<"\tdpath_l:"<<std::showpoint<<dPassPath_L;
	float_t dPassPath_R = Cm * dpluse_r;
	//std::cout<<"\tdpath_r:"<<std::showpoint<<dPassPath_R;
	float_t dPassPath = (dPassPath_R + dPassPath_L) / 2.0;
	std::cout<<"dPassPath:"<<std::showpoint<<dPassPath;
	//float_t dwPassPath = Cm*(dpluse_r - dpluse_l);
	//PassPath = PadPassPath;
	//std::cout<<"\tdwPassPath:"<<std::showpoint<<dwPassPath;

	//对直线进行修正
	float_t dPassHeading = 0.0;
	float_t dPassheadingTemp = Cm * (dpluse_r - dpluse_l) / WheelBase;
	if ((dPassheadingTemp >= -0.00081 && dPassheadingTemp <= 0.00081)) {
		dPassHeading = 0.0;
	}
	else {
		dPassHeading = dPassheadingTemp;
	}
	//float_t dPassHeading = Cm * (dpluse_r - dpluse_l) / WheelBase;
	std::cout<<"\tdPassHeading:"<<std::showpoint<<dPassHeading;
	float_t PreHeading = odom_msg.Pose_Theta;
	float_t AverageHeading = PreHeading +dPassHeading / 2.0;
	std::cout<<"\tAverageHeading:"<<std::showpoint<<AverageHeading;


	odom_msg.Pose_X += dPassPath * cos(AverageHeading);

	std::cout<<"\tcos:"<<std::fixed<<std::setprecision(9)<<cos(AverageHeading);

	//std::cout<<"\tPose_X:"<<std::showpoint<<odom_msg.Pose_X<<std::endl;
	odom_msg.Pose_Y += dPassPath *sin(AverageHeading);
	odom_msg.Pose_Theta += dPassHeading;
	odom_msg.Vx = dPassPath / dt_sec;
	odom_msg.Vyaw = dPassHeading / dt_sec;
	/* }
	  else {
		  odom_msg.Vx = 0.0;
		  odom_msg.Vyaw = 0.0;
		  odom_msg.Pose_X = 0.0;
		  odom_msg.Pose_Y = 0.0;
		  odom_msg.Pose_Theta = 0.0;
		  OdometryInitialized = true;
	}*/
}


#endif /* AGVCMD_CPP_ */
