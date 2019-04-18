#pragma once

template<class T>
T Lerp(T p1, T p2, float d)
{
	return p1 + (p2 - p1) * d;
}