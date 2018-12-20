#ifndef BOX_H
#define BOX_H

class BoundingBox
{
      int left, right, top, bottom;
public:
      BoundingBox();
      BoundingBox(int l, int r, int t, int b);
      void setLeft(int l);
      void setRight(int r);
      void setTop(int t);
      void setBottom(int b);
      int getLeft();
      int getRight();
      int getTop();
      int getBottom();
      bool in(int x, int y);
      void draw();
};

#endif // BOX_H
