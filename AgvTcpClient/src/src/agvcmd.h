/*
 * agvcmd.h
 *
 *  Created on: Aug 1, 2016
 *      Author: agv
 */

#ifndef AGVCMD_H_
#define AGVCMD_H_

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

#endif /* AGVCMD_H_ */
