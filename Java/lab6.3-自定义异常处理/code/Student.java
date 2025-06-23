public class Student {
    private String name;
    private String address;

    private void setname(String name) throws Exception {
        if (name.length() < 1 || name.length() > 5)
            throw new IllegalNameException("name length:" + name.length() + " is not valid.");
        else
            this.name = name;
    }

    private void setaddress(String address) throws Exception {
        char target1 = '省', target2 = '市';
        if (address.indexOf(target1) == -1 && address.indexOf(target2) == -1)
            throw new IllegalAddressException("address is not valid.");
        else
            this.address = address;
    }

    Student(String name, String address) throws Exception {
        try {
            setname(name);
            setaddress(address);
        } catch (Exception e) {
            throw e;
        }
    }
}
