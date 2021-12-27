public class Grade {
    int judgeGrade(int data) {
        int level = 0;
        if (data > 2000)
            level = 1;
        else if (data > 1300 && data <= 2000)
            level = 2;
        else if (data > 800 && data <= 1300)
            level = 3;
        else if (data > 500 && data <= 800)
            level = 4;
        else if (data > 200 && data <= 500)
            level = 5;
        else if (data > 50 && data <= 200)
            level = 6;
        else
            level = 7;
        return level;
    }
}
