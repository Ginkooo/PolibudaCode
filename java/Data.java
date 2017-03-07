/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package data;

import java.util.Scanner;
import java.util.Calendar;

/**
 *
 * @author student
 */
public class Data {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Scanner stdin = new Scanner(System.in);
        System.out.println("Podaj imie: ");
        String name = stdin.nextLine();
        System.out.print("Podaj liczbe dni do przesuniecia: ");
        int days = stdin.nextInt();
        Calendar calendar = Calendar.getInstance();
        System.out.println("Jest teraz: " + calendar.getTime());
        
        calendar.add(Calendar.DATE, days);
        System.out.println("Za " + days + " dni będzie " + calendar.getTime());
    }
    
}
