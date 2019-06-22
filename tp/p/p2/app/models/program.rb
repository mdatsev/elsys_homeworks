class Program < ApplicationRecord
    belongs_to :thread_object, foreign_key: 'thread_id', primary_key: 'thread_id'
end
