#pragma once

class DrawScreen {
public:
	int windowWidth, windowHeight;
	ClusterGroups _CG{ 3 };

	void setWindowSize(RECT _rect);
	void PaintOnScreen(HDC hdc);
	void DrawCircles(Graphics& theGraphics1, SolidBrush& _pen, int _radius, int _offset, std::vector<std::pair<int, int>> _group);
	void DrawLine(Graphics& theGraphics1, Pen& _pen, int _radius, int _offset);
	void DrawPerpendicularLine(Graphics& theGraphics1, Pen& _pen);
};