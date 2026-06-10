#include <stdio.h>
#include <stdlib.h>

#define WIDTH 80
#define HEIGHT 24

#define EMPTY '_'
#define PIXEL '*'

#define MAX_OBJECTS 100

/* Shape type constants */
#define SHAPE_LINE     1
#define SHAPE_RECT     2
#define SHAPE_CIRCLE   3
#define SHAPE_TRIANGLE 4

typedef struct {
    int type;       /* 1=Line, 2=Rectangle, 3=Circle, 4=Triangle */
    int params[6];  /* Up to 6 integer parameters depending on type */
    int active;     /* 1 if object is active, 0 if deleted */
} Shape;

char picture[HEIGHT][WIDTH];
Shape objects[MAX_OBJECTS];
int objectCount = 0;

/* ------------------------------------------------------------------ */
/*  Core canvas functions                                              */
/* ------------------------------------------------------------------ */

void clearPicture() {
    int y, x;
    for (y = 0; y < HEIGHT; y++)
        for (x = 0; x < WIDTH; x++)
            picture[y][x] = EMPTY;
}

void displayPicture() {
    int y, x;
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++)
            printf("%c", picture[y][x]);
        printf("\n");
    }
}

void setPixel(int x, int y) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
        picture[y][x] = PIXEL;
}

/* ------------------------------------------------------------------ */
/*  Drawing primitives                                                 */
/* ------------------------------------------------------------------ */

void drawLine(int x1, int y1, int x2, int y2) {
    /* Bresenham's line algorithm */
    int dx = abs(x2 - x1);
    int dy = -abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1) {
        setPixel(x1, y1);
        if (x1 == x2 && y1 == y2) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x1 += sx; }
        if (e2 <= dx) { err += dx; y1 += sy; }
    }
}

void drawRectangle(int x1, int y1, int x2, int y2) {
    drawLine(x1, y1, x2, y1);  /* Top    */
    drawLine(x1, y2, x2, y2);  /* Bottom */
    drawLine(x1, y1, x1, y2);  /* Left   */
    drawLine(x2, y1, x2, y2);  /* Right  */
}

void drawCircle(int cx, int cy, int radius) {
    /* Midpoint circle algorithm */
    int x = 0, y = radius;
    int d = 1 - radius;

    while (x <= y) {
        setPixel(cx + x, cy + y);
        setPixel(cx - x, cy + y);
        setPixel(cx + x, cy - y);
        setPixel(cx - x, cy - y);
        setPixel(cx + y, cy + x);
        setPixel(cx - y, cy + x);
        setPixel(cx + y, cy - x);
        setPixel(cx - y, cy - x);

        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}

/* ------------------------------------------------------------------ */
/*  Object management helpers                                          */
/* ------------------------------------------------------------------ */

void drawShape(Shape *s) {
    switch (s->type) {
        case SHAPE_LINE:
            drawLine(s->params[0], s->params[1],
                     s->params[2], s->params[3]);
            break;
        case SHAPE_RECT:
            drawRectangle(s->params[0], s->params[1],
                          s->params[2], s->params[3]);
            break;
        case SHAPE_CIRCLE:
            drawCircle(s->params[0], s->params[1], s->params[2]);
            break;
        case SHAPE_TRIANGLE:
            drawTriangle(s->params[0], s->params[1],
                         s->params[2], s->params[3],
                         s->params[4], s->params[5]);
            break;
    }
}

void redrawAll() {
    int i;
    clearPicture();
    for (i = 0; i < objectCount; i++) {
        if (objects[i].active)
            drawShape(&objects[i]);
    }
}

/* Read shape parameters from stdin based on shape type */
void readShapeParams(int shapeType, int params[]) {
    if (shapeType == SHAPE_LINE) {
        printf("Enter x1 y1 x2 y2: ");
        scanf("%d %d %d %d", &params[0], &params[1],
              &params[2], &params[3]);
    } else if (shapeType == SHAPE_RECT) {
        printf("Enter top-left x y and bottom-right x y: ");
        scanf("%d %d %d %d", &params[0], &params[1],
              &params[2], &params[3]);
    } else if (shapeType == SHAPE_CIRCLE) {
        printf("Enter center x y and radius: ");
        scanf("%d %d %d", &params[0], &params[1], &params[2]);
    } else if (shapeType == SHAPE_TRIANGLE) {
        printf("Enter x1 y1 x2 y2 x3 y3: ");
        scanf("%d %d %d %d %d %d", &params[0], &params[1],
              &params[2], &params[3], &params[4], &params[5]);
    }
}

/* ------------------------------------------------------------------ */
/*  Main program                                                       */
/* ------------------------------------------------------------------ */

int main() {
    int choice;

    clearPicture();

    while (1) {
        printf("2D Graphics Editor\n");
        printf("Canvas size: %d x %d\n", WIDTH, HEIGHT);
        printf("1. Add object\n");
        printf("2. Delete object\n");
        printf("3. Modify object\n");
        printf("4. Display picture\n");
        printf("5. List objects\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            /* --- Add object --- */
            int shapeType;
            int idx = objectCount;

            printf("\nChoose shape type:\n");
            printf("1. Line\n");
            printf("2. Rectangle\n");
            printf("3. Circle\n");
            printf("4. Triangle\n");
            printf("Enter shape type: ");
            scanf("%d", &shapeType);

            objects[idx].type = shapeType;
            objects[idx].active = 1;
            readShapeParams(shapeType, objects[idx].params);

            objectCount++;
            printf("Object added with index %d.\n", idx);
        }
        else if (choice == 2) {
            /* --- Delete object --- */
            int idx;
            printf("\nEnter object index to delete: ");
            scanf("%d", &idx);
            if (idx >= 0 && idx < objectCount && objects[idx].active) {
                objects[idx].active = 0;
                printf("Object %d deleted.\n", idx);
            } else {
                printf("Invalid index.\n");
            }
        }
        else if (choice == 3) {
            /* --- Modify object --- */
            int idx;
            printf("\nEnter object index to modify: ");
            scanf("%d", &idx);
            if (idx >= 0 && idx < objectCount && objects[idx].active) {
                printf("Enter new parameters:\n");
                readShapeParams(objects[idx].type, objects[idx].params);
                printf("Object %d modified.\n", idx);
            } else {
                printf("Invalid index.\n");
            }
        }
        else if (choice == 4) {
            /* --- Display picture --- */
            printf("\n");
            redrawAll();
            displayPicture();
        }
        else if (choice == 5) {
            /* --- List objects --- */
            int i;
            printf("\n");
            for (i = 0; i < objectCount; i++) {
                if (!objects[i].active) {
                    printf("Object %d: [deleted]\n", i);
                    continue;
                }
                printf("Object %d: ", i);
                switch (objects[i].type) {
                    case SHAPE_LINE:
                        printf("Line (%d,%d)-(%d,%d)\n",
                               objects[i].params[0], objects[i].params[1],
                               objects[i].params[2], objects[i].params[3]);
                        break;
                    case SHAPE_RECT:
                        printf("Rectangle (%d,%d)-(%d,%d)\n",
                               objects[i].params[0], objects[i].params[1],
                               objects[i].params[2], objects[i].params[3]);
                        break;
                    case SHAPE_CIRCLE:
                        printf("Circle center(%d,%d) radius %d\n",
                               objects[i].params[0], objects[i].params[1],
                               objects[i].params[2]);
                        break;
                    case SHAPE_TRIANGLE:
                        printf("Triangle (%d,%d)-(%d,%d)-(%d,%d)\n",
                               objects[i].params[0], objects[i].params[1],
                               objects[i].params[2], objects[i].params[3],
                               objects[i].params[4], objects[i].params[5]);
                        break;
                }
            }
        }
        else if (choice == 0) {
            printf("Goodbye.\n");
            break;
        }
        else {
            printf("Invalid choice.\n");
        }

        printf("\n");
    }

    return 0;
}
