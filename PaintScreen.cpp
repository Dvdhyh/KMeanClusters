#include "HeaderMaster.h"

void DrawScreen::setWindowSize(RECT _rect) {
	windowWidth = _rect.right - _rect.left;
	windowHeight = _rect.bottom -_rect.top;

	_CG.setWindowSize(_rect);
}

void DrawScreen::PaintOnScreen(HDC hdc) {
	HDC hdcMem = CreateCompatibleDC(hdc);
	const int nMemDC = ::SaveDC(hdcMem);
	HBITMAP hbitMem = CreateCompatibleBitmap(hdc, windowWidth, windowHeight);
	HANDLE hOld = ::SelectObject(hdcMem, hbitMem);

	// Draw into hdcMem here

	Pen thePenBlack(Color(255, 0, 0, 0));

	//If you wish to create more than k=4, then just add more colors here and in the switch  
	SolidBrush theBrushBlue(Color(255, 0, 0, 255));
	SolidBrush theBrushRed(Color(255, 255, 0, 0));
	SolidBrush theBrushGreen(Color(255, 0, 255, 0));
	SolidBrush theBrushBlack(Color(255, 0, 0, 0));


	int _diameter = 10;
	int _radius = _diameter / 2;

	Graphics theGraphics1(hdcMem);
	SolidBrush backgroundWhite(Color(255, 255, 255));
	theGraphics1.FillRectangle(&backgroundWhite, 0, 0, windowWidth, windowHeight);

	int clusterNum = _CG.getK();

	//Create more colors if needed
	if (clusterNum > 0) {

		//X to mark the K points
		for (auto&a : _CG.KPoint) {
			DrawLine(theGraphics1, thePenBlack, a.first, a.second);
		}

		//Draw perpendicular line
		//DrawPerpendicularLine(theGraphics1, thePenBlack);

		//Draw cricles to represent data
		for (int i = 0; i < clusterNum; i++) {
			switch (i) {
			case 0:
				//Using colors to separate data into their groups
				DrawCircles(theGraphics1, theBrushBlue, _diameter, 0, _CG.holdClusters[i]);
				break;
			case 1:
				DrawCircles(theGraphics1, theBrushRed, _diameter, 0, _CG.holdClusters[i]);
				break;
			case 2:
				DrawCircles(theGraphics1, theBrushGreen, _diameter, 0, _CG.holdClusters[i]);
				break;
			case 3:
				DrawCircles(theGraphics1, theBrushBlack, _diameter, 0, _CG.holdClusters[i]);
				break;
			}
		}

		// Place everything on buffer to main HDC
		BitBlt(hdc, 0, 0, windowWidth, windowHeight, hdcMem, 0, 0, SRCCOPY);

		// Return To previous HANDLE before Drawing begin
		SelectObject(hdcMem, hOld);

		RestoreDC(hdcMem, nMemDC);
		//Clean Up 
		DeleteObject(hbitMem);
		DeleteDC(hdcMem);
	}
}

void DrawScreen::DrawCircles(Graphics& theGraphics1, SolidBrush& _pen, int _radius, int _offset, std::vector<std::pair<int, int>> _group) {
	for (int a = 0; a < _group.size(); a++)
		theGraphics1.FillEllipse(&_pen, _group[a].first + _offset, _group[a].second, _radius, _radius);
}

void DrawScreen::DrawLine(Graphics& theGraphics1, Pen& _pen, int _x, int _y) {
	theGraphics1.DrawLine(&_pen, _x - 5, _y - 5, _x + 5, _y + 5);
	theGraphics1.DrawLine(&_pen, _x - 5, _y + 5, _x + 5, _y - 5);
}

void DrawScreen::DrawPerpendicularLine(Graphics& theGraphics1, Pen& _pen) {

	int x1, y1, x2, y2;
	double x3, y3, _c;
	x1 = _CG.KPoint[0].first;
	y1 = _CG.KPoint[0].second;
	x2 = _CG.KPoint[1].first;
	y2 = _CG.KPoint[1].second;

	//Draw a line between the k point
	theGraphics1.DrawLine(&_pen, x1, y1, x2, y2);
	
	
	x3 = (x1 + x2) / 2;
	y3 = (y1 + y2) / 2;

	if (y1 == y2) {
		y1 -= 1;
	}
		
	double grad = -(x2 - x1) / (double)(y2 - y1);

	_c = y3 - grad * x3;

	y1 = grad * 1 + _c;
	y2 = grad * windowHeight + _c;

	x1 = (y1 - _c)/ grad;
	x2 = (y2 - _c)/ grad;

	//Draw the Perpendicular line
	theGraphics1.DrawLine(&_pen, x1, y1, x2, y2);
	
}