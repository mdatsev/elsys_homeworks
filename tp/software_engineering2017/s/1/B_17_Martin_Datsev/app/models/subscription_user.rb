class SubscriptionUser < ApplicationRecord
    belongs_to :user
    belongs_to :subscription
    validate :sub_limit
    def sub_limit
        if(subscription.price < 10)
            all = SubscriptionUser.all
                .select{|e| e.subscription_id == subscription_id}
                .map{|e| e.position}
            all << position
            teachers = all.select{|e| e == "teacher"}
            students = all.select{|e| e == "student"}
            if(teachers.length > 2)
                errors.add(:subscription_id, "of <10 does not allow more than 2 teachers")
            elsif(students.length > 10)
                errors.add(:subscription_id, "of <10 does not allow more than 10 students")
            end
        end
    end
end
