class CreateEncryptMessages < ActiveRecord::Migration[5.1]
  def change
    create_table :encrypt_messages do |t|
      t.references :rsa, foreign_key: true
      t.string :message

      t.timestamps
    end
  end
end
