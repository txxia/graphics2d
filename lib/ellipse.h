#ifndef ELLIPSE_H
#define ELLIPSE_H

#define Sign(x) ((x>0)-(x<0))

extern void NaiveMidpointEllipse(int a, int b,
                          void (*callback)(int, int));

extern void EfficientMidpointEllipse(int a, int b,
                              void (*callback)(int, int));
#endif
