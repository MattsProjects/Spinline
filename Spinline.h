// Spinline.h
// Creates a progress indicator which writes a dotted line led by a spinning icon
//
// Copyright (c) 2016-2019 Matthew Breit - matt.breit@baslerweb.com or matt.breit@gmail.com
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http ://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef SPINLINE_H
#define SPINLINE_H

#ifndef LINUX_BUILD
#define WIN_BUILD
#endif

#include <thread>
#include <atomic>
#include <iostream>

namespace Spinline
{
	class CSpinLine
	{
	private:
		std::thread tspin;
		std::atomic<bool> stop;
		inline static void Spin(std::atomic<bool>& stop);

	public:
		CSpinLine();
		~CSpinLine();
		void Start();
		void Stop();
	};
}

// *********************************************************************************************************
// DEFINITIONS

// progress indicator
inline Spinline::CSpinLine::CSpinLine()
{}

inline Spinline::CSpinLine::~CSpinLine()
{
	this->Stop();
}

inline void Spinline::CSpinLine::Start()
{
	stop = false;
	tspin = std::thread(Spin, std::ref(stop));
}

inline void Spinline::CSpinLine::Stop()
{
	stop = true;
	if (tspin.joinable())
		tspin.join();
}

#ifdef LINUX_BUILD
inline void Spinline::CSpinLine::Spin(std::atomic<bool>& stop)
{
	while (stop == false)
	{
		// not as pretty in Linux as in Windows, but shows some indicator of progress. Not a big deal.
		std::cout << std::flush << ".";
		std::cout << "\\\b";
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		std::cout << "|\b";
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		std::cout << "/\b";
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		std::cout << "_\b";
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	std::cout << std::endl;
}
#endif

#ifdef WIN_BUILD
inline void Spinline::CSpinLine::Spin(std::atomic<bool>& stop)
{
	while (stop == false)
	{
		std::printf(".");
		std::printf("\\\b");
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		std::printf("|\b");
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		std::printf("/\b");
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		std::printf("_\b");
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	std::cout << std::endl;
}
#endif

// *********************************************************************************************************


#endif
