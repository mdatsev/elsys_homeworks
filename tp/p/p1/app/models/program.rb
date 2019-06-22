class Program < ApplicationRecord
    belongs_to :thread_obj, primary_key: 'thread_id', foreign_key: 'thread_id'

end
