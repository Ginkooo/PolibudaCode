package com.example.piotr.lab5;

public class Position {

    public Position(float x, float y) {
        this.x = x;
        this.y = y;
    }

    public Position(Position position) {
        this.x = position.x;
        this.y = position.y;
    }

    public float x;
    public float y;
}
