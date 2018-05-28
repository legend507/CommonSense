
struct rect
{
    int x;
    int y;
    int width;
    int height;
};

bool valueInRange(int value, int min, int max)
{ return (value >= min) && (value <= max); }

bool rectOverlap(rect A, rect B)
{
    // if A is in B or B is in A, fox x axis
    bool xOverlap = valueInRange(A.x, B.x, B.x + B.width) ||
                    valueInRange(B.x, A.x, A.x + A.width);

    // same for y axis
    bool yOverlap = valueInRange(A.y, B.y, B.y + B.height) ||
                    valueInRange(B.y, A.y, A.y + A.height);

    // A and B overlap if and only if both x and y axis overlap
    return xOverlap && yOverlap;
}