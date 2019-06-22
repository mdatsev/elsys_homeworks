class CreateThreadObjs < ActiveRecord::Migration[5.1]
  def change
    create_table :thread_objs do |t|
      t.integer :thread_id
      t.integer :value

      t.timestamps
    end
  end
end
