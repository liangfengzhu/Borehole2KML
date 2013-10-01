#pragma once
/*该文件主要定义了用于保存二维坐标点、钻孔类型、钻孔信息、地层整体信息和地层信息的结构*/
#ifndef BOREHOLE_H
#define BOREHOLE_H
#include <string>
using namespace std;

struct _POINT2D
{
	double m_x;
	double m_y;
};

struct _BOREHOLEINFO
{
	string m_holeCode;//钻孔编号
	string m_holeName;//钻孔名称
	string m_holeType;//钻孔类型
	string m_holeTypeName;//钻孔类型名
	string m_dateStart;//开工日期
	string m_dateEnd;//完工日期
	string m_Engineer;//现场工程师
	string m_mark;//备注
	double m_waterLevel;//地下水位
	double m_holeDiameter;//孔径
	double m_holeDep;//钻孔深度
	double m_holeEle;//孔口高程
	_POINT2D m_pt;//经纬度坐标
};

struct _HOLESTRATAINFO
{
	string m_holeCode;//钻孔编号
	string m_holeName;//钻孔名称
	string m_straCode;//地层编号
	string m_straColor;//地层颜色
	string m_straName;//地层名称
	string m_age;//地层年代
	string m_genesis;//地质成因
	double m_eleTop;//层顶标高
	float m_layerBottomDep;//层底埋深
	float m_layerTopDep;//层顶埋深
	//int m_rcdNo;//整体记录号
	int m_layerNo;//地层序号
};
#endif