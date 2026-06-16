#ifndef DISK_H
#define DISK_H

class Disk {
    private:
    char color; //B, W, .
    public:
    Disk() : color('.') {}//. equals empty

    Disk(char c) {
        color = c;
    }
    char get_color() const {
        return color;
    }
    void set_color(char c) {
        color = c;
    }
    bool is_empty() const {
        return color == '.';
    }
    void flip() {
        if (color == 'B'){
            set_color('W');
        }
        else if (color == 'W') {
            set_color('B');
        }
    }
    bool operator==(const Disk& d) const{
        return color == d.color;
    }
};

#endif
