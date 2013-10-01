#pragma once

#ifndef CREATEKML_PM_H
#define CREATEKML_PM_H
#include <string>
#include <fstream>
#include <sstream>
#include "structFile.h"
#include "ConvertCharset.h"
using namespace std;

const int iSide = 13;//用12边形来表示园
const double PI = 3.1415926;
const double COEFFICIENT = 2*PI/360;//将角度转化为弧度的转化系数
const double SCOPE = 0.009;//表示一千米大约等于0.009经纬度

//创建总体的点地标文件
inline void CreatePointPM(ofstream &fout,_BOREHOLEINFO bhInfo)
{	
	ostringstream ostrPM;
	ostrPM.precision(11);
	ostrPM<<"<Style id = \"PlacemarkStyle\">"<<'\n'
		<<"<IconStyle>"<<'\n'
		<<"  <color>ff0000ff</color>"<<'\n'
		<<"  <Icon>"<<'\n'
		<<"    <href>http://maps.google.com/mapfiles/kml/shapes/placemark_circle.png</href>"<<'\n'
		<<"  </Icon>"<<'\n'
		<<"</IconStyle>"<<'\n'
		<<"<BalloonStyle>"<<'\n'
		<<"<bgColor>ffE6D8AD</bgColor>"<<'\n'
		<<"<textColor>ff000000</textColor>"<<'\n'
		<<"<text><![CDATA[$[description]]]></text>"<<'\n'
		<<"</BalloonStyle>"<<'\n'
		<<"</Style>"<<'\n'
		<<'\n'
		<<"<Placemark>"<<'\n'
		<<"  <name>"<<bhInfo.m_holeName<<"</name>"<<'\n'
		<<"    <description>"<<'\n'
		<<"       <![CDATA[<!DOCTYPE HTML>"<<'\n'
		<<"       <html>"<<'\n'
		<<"       <meta charset=\"utf-8\">"<<'\n'
		<<"       <body>"<<'\n'
		<<"       <title></title>"<<'\n'
		<<"       <style type=\"text/css\">"<<'\n'
		<<"       fieldset{ width:180px; }"<<'\n'
		<<"       p{ font-size:12px; font-weight:bold;}"<<'\n'
		<<"      </style>"<<'\n'
		<<"      <table width=\"200\" cellspacing=\"0\" cellpadding=\"0\" border=\"0\"><tr><td bgcolor=\"#DCDCDC\" valign = \"middle\" align=\"left\"><br/>"<<'\n'
		<<"      <font face=\"Arial\" style=\"font-size: 11pt\" color=\"#000000\" ><strong>"<<bhInfo.m_holeName<<"</strong></font><br/><br/></td></tr>"<<'\n'
		<<"      <tr><td bgcolor=\"#F5F5F5\" valign = \"bottom\" align=\"left\">"<<'\n'
		<<"      <fieldset align=\"left\" style=\" border:2px solid #3D3D3D;\">"<<'\n'
		<<"      <legend><h3><img src=\"http://202.127.1.14/myweb/picture/borehole.png\" valign = \"middle\" align=\"left\" width = \"12\" height = \"25\">&nbsp;&nbsp;Current borehole</h3></legend>"<<'\n'
		<<"      <p><font color=\"#000000\"><b>Borehole code: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_holeCode<<"</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Borehole name: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_holeName<<"</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Borehole type: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_holeTypeName<<"</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Longitude: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_pt.m_x<<"°</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Latitude: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_pt.m_y<<"°</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Hole diameter: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_holeDiameter<<"(mm)</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Elevation: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_holeEle<<"(m)</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Drilling depth: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_holeDep<<"(m)</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Ground water level: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_waterLevel<<"(m)</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Drilling start date: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_dateStart<<"</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Drilling end date: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_dateEnd<<"</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Driller: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_Engineer<<"</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Remarks: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_mark<<"</font><br/></p>"<<'\n'
		<<"      </fieldset>"<<'\n'
		<<"      </td></tr></table>"<<'\n'
		<<"      </body>"<<'\n'
		<<"      </html>"<<'\n'
		<<"      ]]>"<<'\n'
		<<"    </description>"<<'\n'
		<<"    <styleUrl>#PlacemarkStyle</styleUrl>"<<'\n'
		<<"    <altitudeMode>clampToGround</altitudeMode>"<<'\n'
		<<"    <Point>"<<'\n'
		<<"      <coordinates>"<<bhInfo.m_pt.m_x<<","<<bhInfo.m_pt.m_y<<"</coordinates>"<<'\n'
		<<"    </Point>"<<'\n'
		<<"</Placemark>"<<'\n'
		<<'\n'
		<<"<NetworkLink>"<<'\n'
		<<"  <name>strata at "<<bhInfo.m_holeName<<"</name>"<<'\n'
		<<"  <Region>"<<'\n'
		<<"    <LatLonAltBox>"<<'\n'
		<<"      <north>"<<bhInfo.m_pt.m_y + SCOPE<<"</north>"<<'\n'
		<<"      <south>"<<bhInfo.m_pt.m_y - SCOPE<<"</south>"<<'\n'
		<<"      <east>"<<bhInfo.m_pt.m_x + SCOPE<<"</east>"<<'\n'
		<<"      <west>"<<bhInfo.m_pt.m_x - SCOPE<<"</west>"<<'\n'
		<<"    </LatLonAltBox>"<<'\n'
		<<"    <Lod>"<<'\n'
		<<"      <minLodPixels>512</minLodPixels>"<<'\n'
		<<"      <maxLodPixels>-1</maxLodPixels>"<<'\n'
		<<"    </Lod>"<<'\n'
		<<"  </Region>"<<'\n'
		<<"  <Link>"<<'\n'
		<<"    <href>"<<bhInfo.m_holeCode<<"_Cylinder.kml"<<"</href>"<<'\n' //以钻孔名作为多边形地标的文件名
		<<"    <viewRefreshMode>onRegion</viewRefreshMode>"<<'\n'
		<<"  </Link>"<<'\n'
		<<"</NetworkLink>"<<'\n';
	fout<<ASCII2UTF_8(ostrPM.str());
}

//创建点地标链接文件头部
inline void CreatePPMHead(ofstream &fout,string folderName)
{
	ostringstream ostrPPMH;	
	ostrPPMH<<"    <name>"<<folderName<<" </name>"<<'\n'
		<<"    <description></description>"<<'\n';
	fout<<ASCII2UTF_8(ostrPPMH.str());
}
//创建点地标网络链接文件
inline void CreateNetWorkLink(ofstream &fout, _BOREHOLEINFO bhInfo)
{
	ostringstream ostrCNW;	
	ostrCNW<<"<NetworkLink>"<<'\n'
		<<"  <name>"<<bhInfo.m_holeCode<<"("<<bhInfo.m_holeName<<")</name>"<<'\n'
		<<"  <Region>"<<'\n'
		<<"    <LatLonAltBox>"<<'\n'
		<<"      <north>"<<bhInfo.m_pt.m_y+SCOPE<<"</north>"<<'\n'
		<<"      <south>"<<bhInfo.m_pt.m_y-SCOPE<<"</south>"<<'\n'
		<<"      <east>"<<bhInfo.m_pt.m_x+SCOPE<<"</east>"<<'\n'
		<<"      <west>"<<bhInfo.m_pt.m_x-SCOPE<<"</west>"<<'\n'
		<<"    </LatLonAltBox>"<<'\n'
		<<"    <Lod>"<<'\n'
		<<"      <minLodPixels>32</minLodPixels>"<<'\n'
		<<"      <maxLodPixels>-1</maxLodPixels>"<<'\n'
		<<"    </Lod>"<<'\n'
		<<"  </Region>"<<'\n'
		<<"  <Link>"<<'\n'
		<<"    <href>"<<bhInfo.m_holeCode<<"_Point.kml</href>"<<'\n'
		<<"    <viewRefreshMode>onRegion</viewRefreshMode>"<<'\n'
		<<"  </Link>"<<'\n'
		<<"</NetworkLink>"<<'\n';
	fout<<ASCII2UTF_8(ostrCNW.str());
}

//求钻孔（十二边形）各顶点的二维坐标
inline void CalculateCoor2D(_POINT2D pt[], int n, const _POINT2D &straCoor, double radius)
{
	for(int i = 0; i < n-1; i++)
	{
		pt[i].m_x = straCoor.m_x + (radius*sin(i*30*COEFFICIENT));
		pt[i].m_y = straCoor.m_y + (radius*cos(i*30*COEFFICIENT));
	}
	pt[n-1] = pt[0];
}

//生成12边形的kml代码
inline void Create12(ofstream &fout,_POINT2D pt2D[13],double dEle)
{
	ostringstream ostr12;	
	ostr12.precision(11);
	ostr12<<"        <Polygon>"<<'\n'
		<<"          <extrude>0</extrude>"<<'\n'
		<<"          <tessellate>1</tessellate>"<<'\n'
		<<"          <altitudeMode>absolute</altitudeMode>"<<'\n'
		<<"          <outerBoundaryIs>"<<'\n'
		<<"            <LinearRing>"<<'\n'
		<<"              <coordinates>"<<'\n'
		<<"                "<<pt2D[0].m_x<<","<<pt2D[0].m_y<<","<<dEle<<'\n'
		<<"                "<<pt2D[1].m_x<<","<<pt2D[1].m_y<<","<<dEle<<'\n'
		<<"                "<<pt2D[2].m_x<<","<<pt2D[2].m_y<<","<<dEle<<'\n'
		<<"                "<<pt2D[3].m_x<<","<<pt2D[3].m_y<<","<<dEle<<'\n'
		<<"                "<<pt2D[4].m_x<<","<<pt2D[4].m_y<<","<<dEle<<'\n'
		<<"                "<<pt2D[5].m_x<<","<<pt2D[5].m_y<<","<<dEle<<'\n'
		<<"                "<<pt2D[6].m_x<<","<<pt2D[6].m_y<<","<<dEle<<'\n'
		<<"                "<<pt2D[7].m_x<<","<<pt2D[7].m_y<<","<<dEle<<'\n'
		<<"                "<<pt2D[8].m_x<<","<<pt2D[8].m_y<<","<<dEle<<'\n'
		<<"                "<<pt2D[9].m_x<<","<<pt2D[9].m_y<<","<<dEle<<'\n'
		<<"                "<<pt2D[10].m_x<<","<<pt2D[10].m_y<<","<<dEle<<'\n'
		<<"                "<<pt2D[11].m_x<<","<<pt2D[11].m_y<<","<<dEle<<'\n'
		<<"                "<<pt2D[12].m_x<<","<<pt2D[12].m_y<<","<<dEle<<'\n'
		<<"             </coordinates>"<<'\n'
		<<"            </LinearRing>"<<'\n'
		<<"          </outerBoundaryIs>"<<'\n'
		<<"        </Polygon>"<<'\n'<<'\n';
	fout<<ASCII2UTF_8(ostr12.str());
}

//生成四边形的kml代码
inline void Create4(ofstream &fout,_POINT2D pStart, _POINT2D pEnd, double dfEle, double dsEle)
{
	ostringstream ostr4;	
	ostr4.precision(11);
	ostr4<<"        <Polygon>"<<'\n'
		<<"          <extrude>0</extrude>"<<'\n'
		<<"          <tessellate>1</tessellate>"<<'\n'
		<<"          <altitudeMode>absolute</altitudeMode>"<<'\n'
		<<"          <outerBoundaryIs>"<<'\n'
		<<"            <LinearRing>"<<'\n'
		<<"              <coordinates>"<<'\n'
		<<"               "<<pStart.m_x<<","<<pStart.m_y<<","<<dfEle<<'\n' 
		<<"               "<<pEnd.m_x<<","<<pEnd.m_y<<","<<dfEle<<'\n' 
		<<"               "<<pEnd.m_x<<","<<pEnd.m_y<<","<<dsEle<<'\n'
		<<"               "<<pStart.m_x<<","<<pStart.m_y<<","<<dsEle<<'\n'
		<<"               "<<pStart.m_x<<","<<pStart.m_y<<","<<dfEle<<'\n'               
		<<"              </coordinates>"<<'\n'
		<<"            </LinearRing>"<<'\n'
		<<"          </outerBoundaryIs>"<<'\n'
		<<"        </Polygon>"<<'\n'<<'\n';
	fout<<ASCII2UTF_8(ostr4.str());
}

//生成多边形样式的kml代码
inline void CreatePolyStyle(ofstream &fout,string strColor)
{
	ostringstream ostrPS;
	ostrPS<<"    <Style id =\""<<strColor<<"\">"<<'\n'
		<<"      <PolyStyle>"<<'\n'
		<<"        <color>"<<strColor<<"</color>"<<'\n'
		<<"        <colorMode>normal</colorMode>"<<'\n'
		<<"        <fill>1</fill>"<<'\n'
		<<"        <outline>0</outline>"<<'\n'
		<<"      </PolyStyle>"<<'\n'
		<<"      <BalloonStyle>"<<'\n'
		/*<<"      <bgColor>ff1a1a1a</bgColor>"<<'\n'
		<<"      <textColor>ffffffff</textColor>"<<'\n'*/
		<<"     <bgColor>ffE6D8AD</bgColor>"<<'\n'
		<<"     <textColor>ff000000</textColor>"<<'\n'
		<<"      <text><![CDATA[$[description]]]></text>"<<'\n'
		<<"      </BalloonStyle>"<<'\n'
		<<"    </Style>"<<'\n'<<'\n';
	fout<<ASCII2UTF_8(ostrPS.str());
}

//生成地标头的kml代码
inline void CreatePMHead(ofstream &fout, _BOREHOLEINFO bhInfo,_HOLESTRATAINFO hsInfo)
{

	string strTemp = hsInfo.m_straColor.substr(2,6);
	rotate(strTemp.begin(),strTemp.begin()+4,strTemp.end());
	rotate(strTemp.begin()+2,strTemp.begin()+4,strTemp.end());

	ostringstream ostrPMHS;
	ostrPMHS.precision(5);
	ostrPMHS<<"    <Placemark>"<<'\n'
		<<"      <name>"<<bhInfo.m_holeName<<"-"<<hsInfo.m_straCode<<"</name>"<<'\n'
		<<"      <description>"<<'\n'
		<<"<![CDATA[<!DOCTYPE HTML>"<<'\n'
		<<"       <html>"<<'\n'
		<<"    <meta charset=\"utf-8\">"<<'\n'
		<<"       <script>"<<'\n'
		<<"         function draw(id) "<<'\n'
		<<"         {"<<'\n'
		<<"            var canvas = document.getElementById(id);"<<'\n'
		<<"            if (canvas == null) return false;"<<'\n'
		<<"            var context = canvas.getContext('2d');"<<'\n'
		<<"            context.fillStyle = \"#"<<strTemp<<"\";"<<'\n'
		<<"            context.fillRect(0, 5,40, 20);"<<'\n'
		<<"          }"<<'\n'
		<<"       </script> "<<'\n'
		<<"       <body>"<<'\n'
		<<"       <title></title>"<<'\n'
		<<"       <style type=\"text/css\">"<<'\n'
		<<"       fieldset{ width:200px; }"<<'\n'
		<<"      s1 {font-size: 12px; letter-spacing: -1px}"<<'\n'
		<<"       p{ font-size:12px; font-weight:bold;}"<<'\n'
		<<"      </style>"<<'\n'
		<<"      <table width=\"200\" cellspacing=\"0\" cellpadding=\"0\" border=\"0\"><tr><td bgcolor=\"#DCDCDC\" valign = \"middle\" align=\"left\"><br/>"<<'\n'
		<<"      <font face=\"Arial\" style=\"font-size: 11pt\" color=\"#000000\"><strong>Borehole name: "<<bhInfo.m_holeName<<"<br/> Layer No: "<<hsInfo.m_layerNo<<"</h3>"<<"</strong></font><br/><br/></td></tr>"<<'\n'
		<<"      <tr><td bgcolor=\"#F5F5F5\" valign = \"bottom\" align=\"left\">"<<'\n'
		<<"      <fieldset align=\"left\" style=\" border:2px solid #3D3D3D;\" >"<<'\n'
		<<"     <legend><h3><img src=\"http://202.127.1.14/myweb/picture/strata.png\" valign = \"middle\" align=\"left\" width = \"20\" height = \"20\">&nbsp;&nbsp;Current stratum</h3></legend>"<<'\n'
		<<"     <p><font color=\"#000000\"><b>Layer No: </b></font><font color=\"#ff0000\"><i>"<<hsInfo.m_layerNo<<"</i></font><br/>"<<'\n'
		<<"     <font color=\"#000000\"><b>Stratum code: </b></font><font color=\"#ff0000\"><i>"<<hsInfo.m_straCode<<"</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Stratum name: </b></font><font color=\"#ff0000\"><i>"<<hsInfo.m_straName<<"</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Description: </b></font><font color=\"#ff0000\"><i>"<<""<<"</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Depth to the top: </b></font><font color=\"#ff0000\"><i>"<<hsInfo.m_layerTopDep<<"(m)</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Depth to the bottom: </b></font><font color=\"#ff0000\"><i>"<<hsInfo.m_layerBottomDep<<"(m)</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Elevation to the top: </b></font><font color=\"#ff0000\"><i>"<<hsInfo.m_eleTop<<"(m)</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Elevation to the bottom: </b></font><font color=\"#ff0000\"><i>"<<hsInfo.m_eleTop-(hsInfo.m_layerBottomDep-hsInfo.m_layerTopDep)<<"(m)</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Thickness: </b></font><font color=\"#ff0000\"><i>"<<hsInfo.m_layerBottomDep-hsInfo.m_layerTopDep<<"(m)</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Formation age: </b></font><font color=\"#ff0000\"><i>"<<""<<"</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Genesis: </b></font><font color=\"#ff0000\"><i>"<<""<<"</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Overall description: </b></font><font color=\"#ff0000\"><i>"<<""<<"</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Color: </b></font><font color=\"#"<<strTemp<<"\"><s1>██████</s1></font><br/></p>"<<'\n'

		//<<"      <font color=\"#000000\"><b>Color: </b></font><body onLoad=\"draw(\'canvas\');\"><canvas id=\"canvas\" width=\"50\" height=\"20\"/></body><br/></p>"<<'\n'
		<<"      </fieldset>"<<'\n'
	    <<"      </td></tr><tr><td><hr width = 216px align = \"middle\" size = 2 color = \"#3CB371\"></hr>"<<'\n'
        <<"      <hr width = 216px align = \"middle\" size = 2 color = \"#3CB371\"></hr></td></tr>"<<'\n'
		<<"      <tr><td bgcolor=\"#F5F5F5\" valign = \"bottom\" align=\"left\">"<<'\n'
        <<"      <fieldset align=\"left\" style=\" border:2px solid #3D3D3D;\" >"<<'\n';
	fout<<ASCII2UTF_8(ostrPMHS.str());
	ostringstream ostrPMHB;
	ostrPMHB.precision(11);
	ostrPMHB<<"      <legend><h3><img src=\"http://202.127.1.14/myweb/picture/borehole.png\" width = \"12\" height = \"25\" valign = \"middle\">&nbsp;&nbsp;Current borehole</h3></legend>"<<'\n'
		<<"      <p><font color=\"#000000\"><b>Borehole code: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_holeCode<<"</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Borehole name: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_holeName<<"</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Borehole type: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_holeTypeName<<"</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Longitude: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_pt.m_x<<"°</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Latitude: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_pt.m_y<<"°</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Hole diameter: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_holeDiameter<<"(mm)</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Elevation: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_holeEle<<"(m)</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Drilling depth: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_holeDep<<"(m)</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Ground water level: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_waterLevel<<"(m)</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Drilling start date: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_dateStart<<"</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Drilling end date: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_dateEnd<<"</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Driller: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_Engineer<<"</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Remarks: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_mark<<"</font><br/></p>"<<'\n'
		<<"      </fieldset>"<<'\n'
		<<"      </td></tr></table>"<<'\n'
		<<"  </body>"<<'\n'
		<<"  </html>"<<'\n'
		<<"  ]]>"<<'\n'
		<<"      </description>"<<'\n'
		<<"      <styleUrl>#"<<hsInfo.m_straColor<<"</styleUrl>"<<'\n'
		<<"      <MultiGeometry>"<<'\n';
	fout<<ASCII2UTF_8(ostrPMHB.str());
}

//生成地标尾的kml代码
inline void CreatePMRear(ofstream &fout)
{
	ostringstream ostrPMR;
	ostrPMR<<"      </MultiGeometry>"<<'\n'
		<<"    </Placemark>"<<'\n'<<'\n';
	fout<<ASCII2UTF_8(ostrPMR.str());
}

//生成kml文件头部的kml代码
inline void CreateKMLHead(ofstream &fout,string fileName)
{
	fileName += ".kml";
	fout.open(fileName,ios::trunc);
	ostringstream ostrKMLH;
	ostrKMLH<<"<?xml version = \"1.0\" encoding =\"UTF-8\"?>"<<'\n'
		<<"<kml xmlns = \"http://www.opengis.net/kml/2.2\">"<<'\n'
		<<"  <Document>"<<'\n';
	fout<<ASCII2UTF_8(ostrKMLH.str());
}

//生成kml文件尾部的kml代码
inline void CreateKMLRear(ofstream &fout)
{
	ostringstream ostrKMLR;
	ostrKMLR<<"  </Document>"<<'\n'
		<<"</kml>"<<'\n';
	fout<<ASCII2UTF_8(ostrKMLR.str());
	fout.close();
}

//创建每层的交接点的点地标文件
inline void CreatePMForEachLayer(ofstream &fout, _BOREHOLEINFO bhInfo,_HOLESTRATAINFO hsInfoUp,_HOLESTRATAINFO hsInfo, double upHeight,double verScale)
{
	string strTemp1;
	string strTemp2;
	string strColorTemp;
	if(!hsInfoUp.m_straColor.empty())
	{
		strTemp1 = hsInfoUp.m_straColor.substr(2,6);
		rotate(strTemp1.begin(),strTemp1.begin()+4,strTemp1.end());
		rotate(strTemp1.begin()+2,strTemp1.begin()+4,strTemp1.end());
	}
	else
	{
		strTemp1 = "ffffff";
	}
	if(!hsInfo.m_straColor.empty())
	{ 
		strColorTemp = hsInfo.m_straColor;
		strTemp2 = hsInfo.m_straColor.substr(2,6);
		rotate(strTemp2.begin(),strTemp2.begin()+4,strTemp2.end());
		rotate(strTemp2.begin()+2,strTemp2.begin()+4,strTemp2.end());
	}
	else
	{
		strTemp2 = "000000";
		strColorTemp = hsInfoUp.m_straColor;
	}

	ostringstream ostrPMES;
	ostrPMES.precision(5);
	ostrPMES<<"    <Style id = \"PlacemarkStyle"<<hsInfo.m_layerNo<<"\">"<<'\n'
		<<"      <IconStyle>"<<'\n'
		<<"        <color>"<<strColorTemp<<"</color>"<<'\n'
		<<"        <Icon>"<<'\n'
		<<"          <href>http://maps.google.com/mapfiles/kml/shapes/shaded_dot.png</href>"<<'\n'
		<<"        </Icon>"<<'\n'
		<<"        <scale>0.5</scale>"<<'\n'
		<<"      </IconStyle>"<<'\n'
		<<"      <BalloonStyle>"<<'\n'
		/*<<"        <bgColor>ff1a1a1a</bgColor>"<<'\n'
		<<"        <textColor>ffffffff</textColor>"<<'\n'*/
		<<"       <bgColor>ffE6D8AD</bgColor>"<<'\n'
		<<"       <textColor>ff000000</textColor>"<<'\n'
		<<"      <text><![CDATA[$[description]]]></text>"<<'\n'
		<<"      </BalloonStyle>"<<'\n'
		<<"      <LabelStyle>"<<'\n'
        <<"      <color>"<<strColorTemp<<"</color>"<<'\n'
        <<"      <colorMode>normal</colorMode>"<<'\n'
        <<"      <scale>0.6</scale> "<<'\n'
        <<"      </LabelStyle>"<<'\n'
		<<"    </Style>"<<'\n'
		<<'\n'
		<<"    <Placemark>"<<'\n'
		<<"      <name>"<<hsInfoUp.m_eleTop-(hsInfoUp.m_layerBottomDep-hsInfoUp.m_layerTopDep)<<"m</name>"<<'\n'
		<<"        <description>"<<'\n'
		<<"        <![CDATA[<!DOCTYPE HTML>"<<'\n'
		<<"       <html>"<<'\n'
		<<"       <meta charset=\"utf-8\">"<<'\n'
/*		<<"       <script>"<<'\n'
		<<"        function drawUp(id)"<<'\n'
		<<"         {"<<'\n'
		<<"            var canvas = document.getElementById(id);"<<'\n'
		<<"            if (canvas == null) return false;"<<'\n'
		<<"            var context = canvas.getContext('2d');"<<'\n'
		<<"            context.fillStyle = \"#"<<strTemp1<<"\";"<<'\n'
		<<"            context.fillRect(0, 5,40, 20);"<<'\n'
		<<"          }"<<'\n'   
		<<"           function drawDown(id)"<<'\n' 
		<<"         {"<<'\n'
		<<"             var canvas = document.getElementById(id);"<<'\n'
		<<"            if (canvas == null) return false;"<<'\n'
		<<"            var context = canvas.getContext('2d');"<<'\n'
		<<"            context.fillStyle = \"#"<<strTemp2<<"\";"<<'\n'
		<<"            context.fillRect(0, 5,40, 20);"<<'\n'
		<<"          }"<<'\n' 
		<<"        window.onload=function()"<<'\n'
		<<"        {"<<'\n'
		<<"          drawUp('canvas1');"<<'\n'
		<<"          drawDown('canvas2');"<<'\n'  
		<<"        }"<<'\n'
		<<"       </script>"<<'\n'*/      
		<<"       <body>"<<'\n'
		<<"       <title></title>"<<'\n'
		<<"       <style type=\"text/css\">"<<'\n'
		<<"      s2 {font-size: 12px; letter-spacing: -1px}"<<'\n'
		<<"       fieldset{ width:200px; }"<<'\n'
		<<"       p{ font-size:12px; font-weight:bold;}"<<'\n'
		<<"      </style>"<<'\n';

	if(hsInfoUp.m_layerNo == 0)
	{
		ostrPMES<<"      <table width=\"200\" cellspacing=\"0\" cellpadding=\"0\" border=\"0\"><tr><td bgcolor=\"#DCDCDC\" valign = \"middle\" align=\"left\"><br/>"<<'\n'
		    /*<<"      &nbsp;&nbsp;&nbsp;&nbsp;"<<'\n'*/
		    <<"      <font face=\"Arial\" style=\"font-size: 11pt\" color=\"#000000\" align = \"center\"><strong>Borehole name: "<<bhInfo.m_holeName<<"<br/>The top of layer "<<hsInfo.m_layerNo<<"</h3>"<<"</strong></font><br/><br/></td></tr>"<<'\n'
			<<"      <tr><td bgcolor=\"#F5F5F5\" valign = \"bottom\" align=\"left\">"<<'\n'
		    <<"      <fieldset align=\"left\" style=\" border:2px solid #3D3D3D;\" >"<<'\n';
	}
	else if(hsInfo.m_layerNo == 0)
	{
		ostrPMES<<"      <table width=\"200\" cellspacing=\"0\" cellpadding=\"0\" border=\"0\"><tr><td bgcolor=\"#DCDCDC\" valign = \"middle\" align=\"left\"><br/>"<<'\n'
		    /*<<"      &nbsp;&nbsp;&nbsp;&nbsp;"<<'\n'*/
		    <<"      <font face=\"Arial\" style=\"font-size: 11pt\" color=\"#000000\" align = \"center\"><strong>Borehole name: "<<bhInfo.m_holeName<<"<br/>The bottom of layer "<<hsInfoUp.m_layerNo<<"</h3>"<<"</strong></font><br/><br/></td></tr>"<<'\n'
			<<"      <tr><td bgcolor=\"#F5F5F5\" valign = \"bottom\" align=\"left\">"<<'\n'
		    <<"      <fieldset align=\"left\" style=\" border:2px solid #3D3D3D;\" >"<<'\n';
	}
	else
	{
		ostrPMES<<"      <table width=\"200\" cellspacing=\"0\" cellpadding=\"0\" border=\"0\"><tr><td bgcolor=\"#DCDCDC\" valign = \"middle\" align=\"left\"><br/>"<<'\n'
		    /*<<"      &nbsp;&nbsp;&nbsp;&nbsp;"<<'\n'*/
		    <<"      <font face=\"Arial\" style=\"font-size: 11pt\" color=\"#000000\" align = \"center\"><strong>Borehole name: "<<bhInfo.m_holeName<<"<br/>Interface between layer "<<hsInfoUp.m_layerNo<<" and "<<hsInfo.m_layerNo<<"</h3>"<<"</strong></font><br/><br/></td></tr>"<<'\n'
			<<"      <tr><td bgcolor=\"#F5F5F5\" valign = \"bottom\" align=\"left\">"<<'\n'
		    <<"      <fieldset align=\"left\" style=\" border:2px solid #3D3D3D;\" >"<<'\n';		   
	}
	 ostrPMES<<"      <legend><h3><img src=\"http://202.127.1.14/myweb/picture/up.png\" valign = \"middle\" align=\"left\" width = \"20\" height = \"20\">&nbsp;&nbsp;Overlying stratum</h3></legend>"<<'\n';

	if(hsInfoUp.m_layerNo != 0)
	{

		ostrPMES<<"      <p><font color=\"#000000\"><b>Layer No: </b></font><font color=\"#ff0000\"><i>"<<hsInfoUp.m_layerNo<<"</i></font><br/>"<<'\n'
			<<"      <font color=\"#000000\"><b>Stratum code: </b></font><font color=\"#ff0000\"><i>"<<hsInfoUp.m_straCode<<"</i></font><br/>"<<'\n'
			<<"      <font color=\"#000000\"><b>Stratum name: </b></font><font color=\"#ff0000\"><i>"<<hsInfoUp.m_straName<<"</i></font><br/>"<<'\n'
			<<"      <font color=\"#000000\"><b>Elevation to the top: </b></font><font color=\"#ff0000\"><i>"<<hsInfoUp.m_eleTop<<"(m)</i></font><br/>"<<'\n'
			<<"      <font color=\"#000000\"><b>Elevation to the bottom: </b></font><font color=\"#ff0000\"><i>"<<hsInfoUp.m_eleTop-(hsInfoUp.m_layerBottomDep-hsInfoUp.m_layerTopDep)<<"(m)</i></font><br/>"<<'\n'
			<<"      <font color=\"#000000\"><b>Thickness: </b></font><font color=\"#ff0000\"><i>"<<hsInfoUp.m_layerBottomDep-hsInfoUp.m_layerTopDep<<"(m)</i></font><br/>"<<'\n'
			<<"      <font color=\"#000000\"><b>Color: </b></font><font color=\"#"<<strTemp1<<"\"><s2>██████</s2></font><br/></p>"<<'\n';
			
			//<<"      <font color=\"#000000\"><b>Color: </b></font><canvas id=\"canvas1\" width=\"40\" height=\"20\"> </canvas><br/></p>"<<'\n';
	}
	else
	{
		ostrPMES<<"      <p><font color=\"#000000\"><b>Layer No: </b></font><font color=\"#ff0000\"><i>"<<"NULL"<<"</i></font><br/>"<<'\n'
			<<"      <font color=\"#000000\"><b>Stratum code: </b></font><font color=\"#ff0000\"><i>"<<"NULL"<<"</i></font><br/>"<<'\n'
			<<"      <font color=\"#000000\"><b>Stratum name: </b></font><font color=\"#ff0000\"><i>"<<"NULL"<<"</i></font><br/>"<<'\n'
			<<"      <font color=\"#000000\"><b>Elevation to the top: </b></font><font color=\"#ff0000\"><i>"<<"NULL"<<"</i></font><br/>"<<'\n'
			<<"      <font color=\"#000000\"><b>Elevation to the bottom: </b></font><font color=\"#ff0000\"><i>"<<"NULL"<<"</i></font><br/>"<<'\n'
			<<"      <font color=\"#000000\"><b>Thickness: </b></font><font color=\"#ff0000\"><i>"<<"NULL"<<"</i></font><br/>"<<'\n'
			<<"      <font color=\"#000000\"><b>Color: </b></font><font color=\"#"<<strTemp1<<"\"><s2>██████</s2></font><br/></p>"<<'\n';
			//<<"      <font color=\"#000000\"><b>Color: </b></font><canvas id=\"canvas1\" width=\"40\" height=\"20\"> </canvas><br/></p>"<<'\n';
	}
	ostrPMES<<"      </fieldset>"<<'\n'
		<<"      </td></tr><tr><td>"<<'\n'
		<<"      <hr width = 216px style=\"border:1px dashed #3CB371\"></hr>"<<'\n'
		<<"      </td></tr>"<<'\n'
		<<"      <tr><td bgcolor=\"#F5F5F5\" valign = \"bottom\" align=\"left\">"<<'\n'
		<<"      <fieldset align=\"left\" style=\" border:2px solid #3D3D3D;\" >"<<'\n'
		<<"      <legend><h3><img src=\"http://202.127.1.14/myweb/picture/down.png\" valign = \"middle\" align=\"left\" width = \"20\" height = \"20\">&nbsp;&nbsp;Underlying stratum</h3></legend>"<<'\n';
	if(hsInfo.m_layerNo !=0 )
	{
		ostrPMES<<"      <p><font color=\"#000000\"><b>Layer No: </b></font><font color=\"#ff0000\"><i>"<<hsInfo.m_layerNo<<"</i></font><br/>"<<'\n'
			<<"      <font color=\"#000000\"><b>Stratum code: </b></font><font color=\"#ff0000\"><i>"<<hsInfo.m_straCode<<"</i></font><br/>"<<'\n'
			<<"      <font color=\"#000000\"><b>Stratum name: </b></font><font color=\"#ff0000\"><i>"<<hsInfo.m_straName<<"</i></font><br/>"<<'\n'
			<<"      <font color=\"#000000\"><b>Elevation to the top: </b></font><font color=\"#ff0000\"><i>"<<hsInfo.m_eleTop<<"(m)</i></font><br/>"<<'\n'
			<<"      <font color=\"#000000\"><b>Elevation to the bottom: </b></font><font color=\"#ff0000\"><i>"<<hsInfo.m_eleTop-(hsInfo.m_layerBottomDep-hsInfo.m_layerTopDep)<<"(m)</i></font><br/>"<<'\n'
			<<"      <font color=\"#000000\"><b>Thickness: </b></font><font color=\"#ff0000\"><i>"<<hsInfo.m_layerBottomDep-hsInfo.m_layerTopDep<<"(m)</i></font><br/>"<<'\n'
			<<"      <font color=\"#000000\"><b>Color: </b></font><font color=\"#"<<strTemp2<<"\"><s2>██████</s2></font><br/></p>"<<'\n';
			//<<"      <font color=\"#000000\"><b>Color: </b></font><canvas id=\"canvas2\" width=\"40\" height=\"20\"></canvas><br/></p>"<<'\n';
	}
	else
	{
		ostrPMES<<"      <p><font color=\"#000000\"><b>Layer No: </b></font><font color=\"#ff0000\"><i>"<<"NULL"<<"</i></font><br/>"<<'\n'
			<<"      <font color=\"#000000\"><b>Stratum code: </b></font><font color=\"#ff0000\"><i>"<<"NULL"<<"</i></font><br/>"<<'\n'
			<<"      <font color=\"#000000\"><b>Stratum name: </b></font><font color=\"#ff0000\"><i>"<<"NULL"<<"</i></font><br/>"<<'\n'
			<<"      <font color=\"#000000\"><b>Elevation to the top: </b></font><font color=\"#ff0000\"><i>"<<"NULL"<<"</i></font><br/>"<<'\n'
			<<"      <font color=\"#000000\"><b>Elevation to the bottom: </b></font><font color=\"#ff0000\"><i>"<<"NULL"<<"</i></font><br/>"<<'\n'
			<<"      <font color=\"#000000\"><b>Thickness: </b></font><font color=\"#ff0000\"><i>"<<"NULL"<<"</i></font><br/>"<<'\n'
			<<"      <font color=\"#000000\"><b>Color: </b></font><font color=\"#"<<strTemp2<<"\"><s2>██████</s2></font><br/></p>"<<'\n';
			
			//<<"      <font color=\"#000000\"><b>Color: </b></font><canvas id=\"canvas2\" width=\"40\" height=\"20\"></canvas><br/></p>"<<'\n';
	}
	ostrPMES<<"      </fieldset>"<<'\n'
	    <<"      </td></tr><tr><td><hr width = 216px align = \"middle\" size = 2 color = \"#3CB371\"></hr>"<<'\n'
        <<"      <hr width = 216px align = \"middle\" size = 2 color = \"#3CB371\"></hr></td></tr>"<<'\n'
		<<"      <tr><td bgcolor=\"#F5F5F5\" valign = \"bottom\" align=\"left\">"<<'\n';
	fout<<ASCII2UTF_8(ostrPMES.str());

	ostringstream ostrPMEB;   
	ostrPMEB.precision(11);
	ostrPMEB<<"      <fieldset align=\"left\" style=\" border:2px solid #3D3D3D;\" >"<<'\n'
		<<"      <legend><h3><img src=\"http://202.127.1.14/myweb/picture/borehole.png\" valign = \"middle\" align=\"left\" width = \"12\" height = \"25\">&nbsp;&nbsp;Current borehole</h3></legend>"<<'\n'
		<<"      <p><font color=\"#000000\"><b>Borehole code: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_holeCode<<"</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Borehole name: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_holeName<<"</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Borehole type: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_holeTypeName<<"</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Longitude: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_pt.m_x<<"°</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Latitude: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_pt.m_y<<"°</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Hole diameter: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_holeDiameter<<"(mm)</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Elevation: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_holeEle<<"(m)</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Drilling depth: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_holeDep<<"(m)</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Ground water level: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_waterLevel<<"(m)</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Drilling start date: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_dateStart<<"</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Drilling end date: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_dateEnd<<"</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Driller: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_Engineer<<"</i></font><br/>"<<'\n'
		<<"      <font color=\"#000000\"><b>Remarks: </b></font><font color=\"#ff0000\"><i>"<<bhInfo.m_mark<<"</font><br/></p>"<<'\n'
		<<"      </fieldset>"<<'\n'
        <<"      </td></tr></table>"<<'\n'
		<<"  </body>"<<'\n'
		<<"  </html>"<<'\n'
		<<"     ]]>"<<'\n'
		<<"        </description>"<<'\n'
		<<"        <styleUrl>#PlacemarkStyle"<<hsInfo.m_layerNo<<"</styleUrl>"<<'\n'
		<<"        <Point>"<<'\n'
		<<"          <altitudeMode>absolute</altitudeMode>"<<'\n'
		<<"          <coordinates>"<<bhInfo.m_pt.m_x<<","<<bhInfo.m_pt.m_y<<","<<(hsInfo.m_eleTop+upHeight)*verScale-0.45<<"</coordinates>"<<'\n'
		<<"        </Point>"<<'\n'
		<<"    </Placemark>"<<'\n'
		<<'\n';
	fout<<ASCII2UTF_8(ostrPMEB.str());
}
#endif