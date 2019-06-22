class CreateUserSubscriptions < ActiveRecord::Migration[5.1]
  def change
    create_table :user_subscriptions do |t|
      t.integer :user_id
      t.integer :subscription_id
      t.integer :role

      t.timestamps
    end
    	
    add_index :user_subscriptions, ["user_id", "subscription_id"], :unique => true
  end
end
