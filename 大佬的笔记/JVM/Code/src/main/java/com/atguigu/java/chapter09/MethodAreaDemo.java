package com.atguigu.java.chapter09;

public class MethodAreaDemo {
    public static void main(String[] args) {
        System.out.println("Start...");
        try {
            Thread.sleep(1000000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("End...");
    }
}
