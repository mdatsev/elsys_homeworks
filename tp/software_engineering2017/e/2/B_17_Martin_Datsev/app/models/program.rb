class Program < ApplicationRecord
<<<<<<< HEAD
    
=======
    validates :thread_id, inclusion: { in: ThreadObj.all.map { |e| e.thread_id },
        message: "thread %{value} is does not exist" }
>>>>>>> 03df20c1bf85863abd238ff32839656daa6ae3b1
end
