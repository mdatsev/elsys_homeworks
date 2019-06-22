package org.elsys.streams.practice;

import java.util.List;

public class OldestPerson {

    public static Person getOldestPerson(List<Person> people) {
        return people.stream().max((a, b) -> a.getAge() - b.getAge()).get();
    }

}
