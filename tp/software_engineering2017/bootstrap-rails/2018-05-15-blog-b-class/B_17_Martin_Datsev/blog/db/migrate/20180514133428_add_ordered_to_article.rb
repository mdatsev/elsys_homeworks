class AddOrderedToArticle < ActiveRecord::Migration[5.0]
  def change
  	add_column :articles, :ordered_first, :boolean, default: false
  end
end
