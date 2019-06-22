package org.elsys.streams.practice;

import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

public class Kids {

    public static Set<String> getKidNames(List<Person> people) {
        return getKidsAgeByName(people).keySet();
    }

    public static Map<String, Integer> getKidsAgeByName(List<Person> people) {
        return people.stream()
        		.filter(p -> p.getAge() < 18)
        		.collect(Collectors.toMap(
        				p -> p.getName(), p -> p.getAge()));
    }

}
