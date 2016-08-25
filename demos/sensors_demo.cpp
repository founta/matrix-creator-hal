/*
 * Copyright 2016 <Admobilize>
 * MATRIX Labs  [http://creator.matrix.one]
 * This file is part of MATRIX Creator HAL
 *
 * MATRIX Creator HAL is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <unistd.h>
#include <iostream>

#include "../cpp/driver/imu_data.h"
#include "../cpp/driver/imu_sensor.h"
#include "../cpp/driver/pressure_data.h"
#include "../cpp/driver/pressure_sensor.h"
#include "../cpp/driver/humidity_data.h"
#include "../cpp/driver/humidity_sensor.h"
#include "../cpp/driver/wishbone_bus.h"

namespace hal = matrix_hal;

int main() {
  hal::WishboneBus* bus = new hal::WishboneBus();
  bus->SpiInit();

  hal::IMUSensor imu_sensor;
  imu_sensor.Setup(bus);

  hal::PressureSensor pressure_sensor;
  pressure_sensor.Setup(bus);

  hal::HumiditySensor humidity_sensor;
  humidity_sensor.Setup(bus);


  hal::IMUData imu_data;
  hal::PressureData pressure_data;
  hal::HumidityData humidity_data;

  while (true) {

    imu_sensor.Read(&imu_data);
    pressure_sensor.Read(&pressure_data);
    humidity_sensor.Read(&humidity_data);


    std::cout << "yaw = " << imu_data.yaw << "\t";
    std::cout << "roll = " << imu_data.roll << "\t";
    std::cout << "pitch = " << imu_data.pitch << std::endl;

    std::cout << "humidity = " << humidity_data.humidity << std::endl;
    std::cout << "temperature = " << humidity_data.temperature << std::endl;

    std::cout << "pressure = " << pressure_data.pressure << std::endl;
    std::cout << "altitude = " << pressure_data.altitude << std::endl;
    std::cout << "temperature = " << pressure_data.temperature << std::endl;

    std::cout << std::endl << std::endl;

    usleep(200000);
  }

  return 0;
}