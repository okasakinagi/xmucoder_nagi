public class Match {
    private static final String user_res = "[a-zA-Z_]\\w*";
    private static final String password_res = "\\w{8,}";
    private static final String email_res = "([^\\s@])+@([^\\s@])+\\.([^\\s@])+(.[^\\\\s@])*";

    public static boolean match_user(String str) {
        return str.matches(user_res);
    }

    public static boolean match_password(String str) {
        return str.matches(password_res);
    }

    public static boolean match_email(String str) {
        return str.matches(email_res);
    }
}
