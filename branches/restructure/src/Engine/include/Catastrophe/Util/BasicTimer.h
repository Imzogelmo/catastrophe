// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#include <time.h>
#include <math.h>


class BasicTimer
{
public:
	BasicTimer() : minutes(0), seconds(0.f), start_time(0), finish_time(0) {}

	int GetMinutes() const
	{
		return minutes;
	}

	float GetSeconds() const
	{
		return seconds;
	}

	long GetStartTime()
	{
		return start_time;
	}

	long GetFinishTime()
	{
		return finish_time;
	}

	void StartTimer()
	{
		start_time = clock();
	}

	void StopTimer()
	{
		finish_time = clock();
		ComputeTime();
	}

	void ComputeTime()
	{
		double elapsed_seconds = (finish_time - start_time) / (double)CLOCKS_PER_SEC;
		minutes = int( elapsed_seconds / 60.0 );
		seconds = float( fmod(elapsed_seconds, 60.0) );
	}

	void ResetTimer()
	{
		*this = BasicTimer();
	}

protected:
	int		minutes;
	float	seconds;
	long	start_time;
	long	finish_time;
};
