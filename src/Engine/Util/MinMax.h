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

#ifndef NO_MINMAX
	#define NO_MINMAX
#endif

#ifdef min
	#undef min
#endif
#ifdef max
	#undef max
#endif


template<class T>
struct MinMax
{
	T min, max;

	MinMax() {}
	MinMax( const T& _Min, const T& _Max ) : min(_Min), max(_Max) 
	{}

	void Set( const T& _Min, const T& _Max )
	{
		min = _Min;
		max = _Max;
	}

	void ApplyMin( const T& _Min )
	{
		if(min < _Min) min = _Min;
		if(max < _Min) max = _Min;
	}

	void ApplyMax( const T& _Max )
	{
		if(min > _Max) min = _Max;
		if(max > _Max) max = _Max;
	}

	// clamps low, high values to min, max.
	void Clamp( const MinMax<T>& m )
	{
		ApplyMin(m.min);
		ApplyMax(m.max);
	}

	void Swap()
	{
		T temp = min;
		min = max;
		max = temp;
	}

	// test equality of min, max.
	bool Equals()
	{
		return min == max;
	}

};