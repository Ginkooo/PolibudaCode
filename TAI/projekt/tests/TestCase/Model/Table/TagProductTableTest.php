<?php
namespace App\Test\TestCase\Model\Table;

use App\Model\Table\TagProductTable;
use Cake\ORM\TableRegistry;
use Cake\TestSuite\TestCase;

/**
 * App\Model\Table\TagProductTable Test Case
 */
class TagProductTableTest extends TestCase
{

    /**
     * Test subject
     *
     * @var \App\Model\Table\TagProductTable
     */
    public $TagProduct;

    /**
     * Fixtures
     *
     * @var array
     */
    public $fixtures = [
        'app.tag_product'
    ];

    /**
     * setUp method
     *
     * @return void
     */
    public function setUp()
    {
        parent::setUp();
        $config = TableRegistry::exists('TagProduct') ? [] : ['className' => TagProductTable::class];
        $this->TagProduct = TableRegistry::get('TagProduct', $config);
    }

    /**
     * tearDown method
     *
     * @return void
     */
    public function tearDown()
    {
        unset($this->TagProduct);

        parent::tearDown();
    }

    /**
     * Test initialize method
     *
     * @return void
     */
    public function testInitialize()
    {
        $this->markTestIncomplete('Not implemented yet.');
    }

    /**
     * Test validationDefault method
     *
     * @return void
     */
    public function testValidationDefault()
    {
        $this->markTestIncomplete('Not implemented yet.');
    }
}
