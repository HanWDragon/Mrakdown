package com.atguigu.java.chapter05;

public class SlotTest {
    public void localVar() {
        int a = 0;
        System.out.println(a);
        int b = 0;
    }

    public void localVar1() {
        {
            int a = 0;
            System.out.println(a);
        }

        int b = 0;
    }
}
