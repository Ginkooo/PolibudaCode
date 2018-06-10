package com.example.piotr.lab5;

;

public class Action {

    public Action(float x, float y, int color) {
        this.x = x;
        this.y = y;
        this.color = color;
        this.type = ACTION_TYPE.LINE;
    }

    public float x;
    public float y;
    public int color;
    public ACTION_TYPE type;
}
