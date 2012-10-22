#ifndef TWODSIZE_H
#define TWODSIZE_H

class twoDSize {
private:
	int width;
	int height;

public:
	twoDSize(int w, int h);
	~twoDSize();

	int getWidth();
	int getHeight();

	void setWidth(int);
	void setHeight(int);
};

#endif

