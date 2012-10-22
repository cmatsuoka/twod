#ifndef TWODPOSITION_H
#define TWODPOSITION_H

class twoDPosition {
private:
	int x;
	int y;

public:
	twoDPosition(int x, int y);
	~twoDPosition();

	int getX();
	int getY();

	void setX(int);
	void setY(int);

	void moveX(int);
	void moveY(int);
};

#endif

