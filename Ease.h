#pragma once

//float GetEase(float start, float end, float rate) {
//	return (end - start) * rate + start;
//}


//�e���v���[�g�ŏ���
template<typename T>
T GetEase(T start, T end, float rate) {
	return (end - start) * rate + start;
}