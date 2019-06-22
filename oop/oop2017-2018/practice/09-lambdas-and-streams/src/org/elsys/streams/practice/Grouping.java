package org.elsys.streams.practice;

import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Grouping {

    public static Map<String, List<Person>> groupByNationality(List<Person> people) {
        return people.stream()
        		.collect(Collectors.groupingBy(p -> p.getNationality()));
    }

    public static Map<String, List<String>> groupNamesByNationality(List<Person> people) {
        return groupByNationality(people).entrySet().stream()
        		.collect(Collectors.toMap(
        				e -> e.getKey(), 
        				e -> e.getValue().stream()
        					  .map(p -> p.getName())
        					  .collect(Collectors.toList())));
    }

}
